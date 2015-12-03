
#include "stdafx.h"
#include "SLIC_superpixels.h"
#include <numeric>

SLICSuperpixel::SLICSuperpixel() {

}

SLICSuperpixel::SLICSuperpixel(Mat& src, int no_of_superpixels, int m, int max_iterations) {


	/* Grid interval (S) = sqrt( N / k ) */
	this->SampleStepSize = int(sqrt((1.0 * src.rows * src.cols) / no_of_superpixels));
	this->NumSuperpixels = no_of_superpixels;
	this->ColorDistanceWeight = int(0.6*SampleStepSize);
	this->maxIterations = max_iterations;

	ImageRGB = src.clone();
	cvtColor(src, ImageLab, CV_BGR2Lab);

	/* Initialize cluster centers Ck and move them to the lowest gradient position in 3x3 neighborhood */
	// This is problematic in 2 ways:
	// 1. do we need to blur it?
	// 2. how about using RGB value instead of Lab value?
	for (int y = SampleStepSize; y < ImageLab.rows - SampleStepSize / 2; y += SampleStepSize) {
		for (int x = SampleStepSize; x < ImageLab.cols - SampleStepSize / 2; x += SampleStepSize) {
			Point2i minimum = findLocalMinimum(ImageLab, Point2i(x, y));
			Vec3b color = ImageLab.at<Vec3b>(minimum.y, minimum.x);
			centers.push_back(ColorRep(color, minimum));
		}
	}

	/* Set labels to -1 and distances to infinity */
	clusters = Mat(ImageLab.size(), CV_32SC1, Scalar(-1));
	distances = Mat(ImageLab.size(), CV_64FC1, Scalar(std::numeric_limits<float>::max()));

	centerCounts = vector<int>(centers.size(), 0);
}


/**
* Clear everything
*/
//void SLICSuperpixel::clear() {
//	centers.clear();
//	centerCounts.clear();
//
//	if (!ImageLab.empty())
//		ImageLab.release();
//}

/**
* Apply the superpixel algorithm in order to obtain cluster centers for each
* superpixel
*/
void SLICSuperpixel::generateSuperPixels() {
	/* Repeat until we hit max iterations (or certain threshold in literature) */
	for (int iter = 0; iter < this->maxIterations; iter++) {

		/* Reset distances */
		distances = Scalar(std::numeric_limits<float>::max());
		/* For each cluster centers Ck */
		for (int k = 0; k < centers.size(); k++) {
			ColorRep center = centers[k];

			/* For each 2 x Steps region around Ck */
			for (int y = (int)(center.y - SampleStepSize); y < center.y + SampleStepSize; y++){
				Vec3b * ptr = ImageLab.ptr<Vec3b>(y);
				int * clust_ptr = clusters.ptr<int>(y);
				double * dist_ptr = distances.ptr<double>(y);

				for (int x = (int)(center.x - SampleStepSize); x < center.x + SampleStepSize; x++){
					if (withinRange(x, y)){
						Vec3b color = ptr[x];

						/* Compute and retain the smaller distance */
						double distance = calcDistance(center, color, x, y);
						if (distance < dist_ptr[x]) {
							dist_ptr[x] = distance;
							clust_ptr[x] = k;
						}
					}
				}
			}
		}

		centers.assign(centers.size(), ColorRep());
		centerCounts.assign(centerCounts.size(), 0);

		/* Update new cluster centers ... */
		for (int y = 0; y < ImageLab.rows; y++) {
			int * clust_ptr = clusters.ptr<int>(y);

			for (int x = 0; x < ImageLab.cols; x++) {
				int cluster_id = clust_ptr[x];
				if (cluster_id > -1) {
					Vec3b color = ImageLab.at<Vec3b>(y, x);
					centers[cluster_id].add(color, x, y);
					centerCounts[cluster_id]++;
				}
			}
		}

		/* ... average them */
		for (int i = 0; i < (centers.size()); i = i + 1) {
			centers[i].div((float)centerCounts[i]);
		}
	}

}


vector<ColorRep> SLICSuperpixel::getCenters() {
	return vector<ColorRep>(centers);
}

/**
* Return to cluster centers for each superpixel
*/
vector<Point2i> SLICSuperpixel::getClusterCenters() {
	vector<Point2i> result(centers.size());

	for (int i = 0; i < (centers.size()); i = i + 1) {
		result[i].x = (int)centers[i].x;
		result[i].y = (int)centers[i].y;
	};

	return result;
}

/**
* Get contour separating each clusters
*/
vector<Point2i> SLICSuperpixel::getContours() {
	const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	vector<vector<bool>> taken;
	for (int y = 0; y < ImageLab.rows; y++)
		taken.push_back(vector<bool>(ImageLab.cols, false));

	vector<Point2i> contours;
	for (int y = 0; y < ImageLab.rows; y++){
		int * clust_ptr = clusters.ptr<int>(y);

		for (int x = 0; x < ImageLab.cols; x++) {
			int nr_p = 0;

			for (int k = 0; k < 8; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];

				if (withinRange(nx, ny)){
					if (!taken[ny][nx] && clust_ptr[x] != clusters.at<int>(ny, nx)) {
						nr_p++;

						if (nr_p > 1)
							break;
					}
				}
			}

			if (nr_p > 1) {
				contours.push_back(Point2i(x, y));
				taken[y][x] = true;
			}
		}
	}

	return contours;
}


/**
* Check if x and y are inside the image
*/
inline bool SLICSuperpixel::withinRange(int x, int y) {
	return x >= 0 && y >= 0 && x < ImageLab.cols && y < ImageLab.rows;
}

/**
* Find local minimum within 3x3 region from the center position
*/
Point2i SLICSuperpixel::findLocalMinimum(Mat& image, Point2i center) {
	Point2i minimum(center.x, center.y);
	float min_gradient = std::numeric_limits<float>::max();

	for (int y = center.y - 1; y < center.y + 2; y++) {
		for (int x = center.x - 1; x < center.x + 2; x++) {
			Vec3b lab = image.at<Vec3b>(y, x);
			Vec3b lab_dy = image.at<Vec3b>(y + 1, x);
			Vec3b lab_dx = image.at<Vec3b>(y, x + 1);

			float diff = fabs((float)(lab_dy[0] - lab[0])) + fabs((float)(lab_dx[0] - lab[0]));
			if (diff < min_gradient) {
				min_gradient = diff;
				minimum.x = x;
				minimum.y = y;
			}
		}
	}

	return minimum;
}

/**
* Calculate distance measure by:
* Dlab = L2 norm( lab color space )
* Dxy  = L2 norm( coordinates )
* Ds   = sqrt( (Dlab / m)^2 + (Dlab / grid interval)^2 )
*/
double SLICSuperpixel::calcDistance(ColorRep& c, Vec3b& p, int x, int y) {
	double d_lab = ((c.l - p[0]) * (c.l - p[0])
		+ (c.a - p[1]) * (c.a - p[1])
		+ (c.b - p[2]) * (c.b - p[2]));

	double d_xy = ((c.x - x) * (c.x - x)
		+ (c.y - y) * (c.y - y));

	return sqrt(d_lab + d_xy / (SampleStepSize * SampleStepSize) * (ColorDistanceWeight * ColorDistanceWeight));
}


int SLICSuperpixel::getS() {
	return this->SampleStepSize;
}

int SLICSuperpixel::getM() {
	return this->ColorDistanceWeight;
}

/**
* Returns a copy of clusters index mapping for each pixel
* i.e. each cell in the matrix shows which cluster index it is
* assigned to
*/
Mat SLICSuperpixel::getClustersIndex() {
	return clusters.clone();
}

/**
* Return the CIELab color space image
*/
Mat SLICSuperpixel::getImage() {
	return ImageRGB.clone();
}

void SLICSuperpixel::recolor2(cv::Mat inputRGB, cv::Mat & output)
{
	output = inputRGB.clone();

	vector<Vec3f> colors(centers.size());


	for (int y = 0; y < output.rows; y++) {
		for (int x = 0; x < output.cols; x++)
			colors[clusters.at<int>(y, x)] += output.at<Vec3b>(y, x);
	}
	/* Get the average of the colors */
	for (int i = 0; i < (colors.size()); i = i + 1) {
		colors[i] /= centerCounts[i];
	};

	for (int y = 0; y < output.rows; y = y + 1) {

		for (int x = 0; x < output.cols; x++) {

			output.at<Vec3b>(y, x) = (Vec3b)colors[clusters.at<int>(y, x)];
		}
	};
}
