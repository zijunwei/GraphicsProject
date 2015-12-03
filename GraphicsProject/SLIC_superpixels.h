
// The code is adapted from Pascal Mettes' https://github.com/PSMM/SLIC-Superpixels
// The cpde is adapted from https://github.com/subokita/Sandbox/tree/master/SLIC%20Superpixels
#ifndef __SLIC_Superpixels__SLIC__
#define __SLIC_Superpixels__SLIC__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ColorRep;

class SLICSuperpixel {
protected:
	Mat clusters;
	Mat distances;
	vector<ColorRep> centers;
	vector<int> centerCounts;

	Mat ImageLab;
	Mat ImageRGB;
	int NumSuperpixels;
	int SampleStepSize;
	int ColorDistanceWeight;
	int maxIterations;

	inline bool withinRange(int x, int y);
	double calcDistance(ColorRep& c, Vec3b& p, int x, int y);
	Point2i findLocalMinimum(Mat& image, Point2i center);

public:
	SLICSuperpixel();
	SLICSuperpixel(Mat& src, int no_of_superpixels, int m = 20, int max_iterations = 50);

	void init(Mat& src, int no_of_superpixels, int m = 20, int max_iterations = 50);
	void clear();
	void generateSuperPixels();

	int getS();
	int getM();

	Mat recolor();
	void recolor2(cv::Mat inputRGB, cv::Mat & output);
	Mat getClustersIndex();
	vector<ColorRep> getCenters();
	vector<Point2i> getClusterCenters();
	vector<Point2i> getContours();
	Mat getImage();
};


/**
* 5 dimension color representation, i.e
* color represented in LAB color space and X Y coords
* It's a struct, well struct behaves like class
*/
class ColorRep{
public:
	float l = 0;
	float a = 0;
	float b = 0;
	float x = 0;
	float y = 0;

	ColorRep(){}

	ColorRep(Vec3b& color, Point2i coord) {
		init(color, coord.x, coord.y);
	}

	ColorRep(Vec3b& color, int x, int y) {
		init(color, x, y);
	}

	void init(Vec3b& color, int x, int y) {
		this->l = color[0];
		this->a = color[1];
		this->b = color[2];
		this->x = (float) x;
		this->y = (float) y;
	}

	void add(Vec3b& color, int x, int y) {
		this->l += color[0];
		this->a += color[1];
		this->b += color[2];
		this->x += x;
		this->y += y;
	}

	void divColor(float divisor) {
		this->l /= divisor;
		this->a /= divisor;
		this->b /= divisor;
	}

	void div(float divisor) {
		this->l /= divisor;
		this->a /= divisor;
		this->b /= divisor;
		this->x /= divisor;
		this->y /= divisor;
	}

	double colorDist(const ColorRep& other) {
		return (this->l - other.l) * (this->l - other.l)
			+ (this->a - other.a) * (this->a - other.a)
			+ (this->b - other.b) * (this->b - other.b);
	}


	double coordDist(const ColorRep& other) {
		return (this->x - other.x) * (this->x - other.x)
			+ (this->y - other.y) * (this->y - other.y);
	}

	//string toString() {
	//	stringstream ss;
	//	ss << l << " " << a << " " << b << " " << x << " " << y;
	//	return ss.str();
	//}
};

#endif /* defined(__SLIC_Superpixels__SLIC__) */
