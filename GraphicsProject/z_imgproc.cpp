#include "stdafx.h"
#include "math.h"
#include "slic.h"
#include <vector>
#include "z_imgproc.h"
using namespace cv;
using namespace std;
void getGradients(Mat inputArray, Mat  & grad_x, Mat & grad_y, Mat & grad_magnitude, Mat & grad_orientation){

	cvtColor(inputArray, inputArray, CV_RGB2GRAY);
	
	 grad_magnitude = cv::Mat::zeros(inputArray.rows, inputArray.cols, CV_64FC1);
	 grad_orientation = cv::Mat::zeros(inputArray.rows, inputArray.cols, CV_64FC1);

	 cv::Sobel(inputArray, grad_x, CV_64FC1, 1, 0, 3);
	 cv::Sobel(inputArray, grad_y, CV_64FC1, 0, 1, 3);

	
	for (int i = 0; i < grad_x.rows; i++){
		for (int j = 0; j < grad_x.cols; j++){
			grad_magnitude.at<double>(i, j) =  sqrt( pow(grad_x.at<double>(i, j), 2) + pow(grad_y.at<double>(i, j), 2));
			grad_orientation.at<double>(i, j) = atan2(grad_y.at<double>(i, j), grad_x.at<double>(i, j));

		
		}
	}



}

void imgStats::imgStatsInit(Mat inputImg){
	
	getGradients(inputImg, this->grad_x, this->grad_y, this->grad_magnitude, this->grad_orientation);

}

//cv::Mat segmentImage1(cv::Mat src){
//
//	// convert the background from pure while to pure black...
//	for (int x = 0; x < src.rows; x++) {
//		for (int y = 0; y < src.cols; y++) {
//			if (src.at<Vec3b>(x, y) == Vec3b(255, 255, 255)) {
//				src.at<Vec3b>(x, y)[0] = 0;
//				src.at<Vec3b>(x, y)[1] = 0;
//				src.at<Vec3b>(x, y)[2] = 0;
//			}
//		}
//	}
//	Mat kernel = (Mat_<float>(3, 3) <<
//		1, 1, 1,
//		1, -8, 1,
//		1, 1, 1); // an approximation of second derivative, a quite strong kernel
//
//
//	// do the laplacian filtering as it is
//	// well, we need to convert everything in something more deeper then CV_8U
//	// because the kernel has some negative values,
//	// and we can expect in general to have a Laplacian image with negative values
//	// BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
//	// so the possible negative number will be truncated
//
//	Mat imgLaplacian;
//	Mat sharp = src; // copy source image to another temporary one
//	filter2D(sharp, imgLaplacian, CV_32F, kernel);
//	src.convertTo(sharp, CV_32F);
//	Mat imgResult = sharp - imgLaplacian;
//	// convert back to 8bits gray scale
//	imgResult.convertTo(imgResult, CV_8UC3);
//	imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
//
//	// convert back to 8bits gray scale
//	imgResult.convertTo(imgResult, CV_8UC3);
//	imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
//	// imshow( "Laplace Filtered Image", imgLaplacian );
//	//imshow("New Sharped Image", imgResult);
//	src = imgResult; // copy back
//	// Create binary image from source image
//	Mat bw;
//	cvtColor(src, bw, CV_BGR2GRAY);
//	threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//	//imshow("Binary Image", bw);
//	// Perform the distance transform algorithm
//	Mat dist;
//	distanceTransform(bw, dist, CV_DIST_L2, 3);
//	// Normalize the distance image for range = {0.0, 1.0}
//	// so we can visualize and threshold it
//	normalize(dist, dist, 0, 1., NORM_MINMAX);
//	//imshow("Distance Transform Image", dist);
//	// Threshold to obtain the peaks
//	// This will be the markers for the foreground objects
//	threshold(dist, dist, .4, 1., CV_THRESH_BINARY);
//	// Dilate a bit the dist image
//	Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
//	dilate(dist, dist, kernel1);
//	//imshow("Peaks", dist);
//	// Create the CV_8U version of the distance image
//	// It is needed for findContours()
//	Mat dist_8u;
//	dist.convertTo(dist_8u, CV_8U);
//	// Find total markers
//	std::vector<std::vector<Point> > contours;
//	findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//	// Create the marker image for the watershed algorithm
//	Mat markers = Mat::zeros(dist.size(), CV_32SC1);
//	// Draw the foreground markers
//	for (size_t i = 0; i < contours.size(); i++)
//		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);
//	// Draw the background marker
//	circle(markers, Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
//	//imshow("Markers", markers * 10000);
//	// Perform the watershed algorithm
//	watershed(src, markers);
//	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
//	markers.convertTo(mark, CV_8UC1);
//	bitwise_not(mark, mark);
//	//    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
//	// image looks like at that point
//	// Generate random colors
//	vector<Vec3b> colors;
//	for (size_t i = 0; i < contours.size(); i++)
//	{
//		int b = theRNG().uniform(0, 255);
//		int g = theRNG().uniform(0, 255);
//		int r = theRNG().uniform(0, 255);
//		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
//	}
//	// Create the result image
//	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
//	// Fill labeled objects with random colors
//	for (int i = 0; i < markers.rows; i++)
//	{
//		for (int j = 0; j < markers.cols; j++)
//		{
//			int index = markers.at<int>(i, j);
//			if (index > 0 && index <= static_cast<int>(contours.size()))
//				dst.at<Vec3b>(i, j) = colors[index - 1];
//			else
//				dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
//		}
//	}
//
//	return dst;
//
//}


//cv::Mat segmentImage2(cv::Mat segImg){
//
//
//	// create segmentation method 1 uisng slic, but problematic...
//	int n_seg_regions = 400;
//	cv::Mat lab_segImg = segImg.clone();
//	cvtColor(lab_segImg, lab_segImg, CV_RGB2Lab);
//	double step = sqrt(lab_segImg.cols*lab_segImg.rows / (double)n_seg_regions);
//	Slic slic;
//
//	// convert mat to iplimage:
//	IplImage* ipl_lab_segImg, *ipl_segImg;
//	ipl_lab_segImg = cvCreateImage(cvSize(lab_segImg.cols, lab_segImg.rows), 8, 3);
//	ipl_segImg = cvCreateImage(cvSize(segImg.cols, segImg.rows), 8, 3);
//	IplImage ipllab = lab_segImg;
//	IplImage iplseg = segImg;
//
//	cvCopy(&ipllab,ipl_lab_segImg );
//	cvCopy(&iplseg, ipl_segImg);
//
//	slic.generate_superpixels(&ipllab, step, n_seg_regions);
//
//	slic.create_connectivity(&iplseg);
//
//	/* Display the contours and show the result. */
//	slic.display_contours( &iplseg, CV_RGB(255, 0, 0));
//	//slic.colour_with_cluster_means(&iplseg);
//	segImg = cv::cvarrToMat(&iplseg);
//	Mat dst = segImg.clone();
//	return dst;
//	//cv::namedWindow("Segmentation", 0);
//	//cv::imshow("Segmentation",segImg);
//}