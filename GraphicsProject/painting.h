#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include <list>
#include "myStroke.h"


//namespace painting{
// brush model variables:

	//class brushParams{
	//public:
	//	double sizeration;   // the size
	//	double whratio;     //  fix w ratio to be 1, h ratio is w*whratio 
	//	double orientation; // 360 degrees.
	//	cv::Mat color;
	//	cv::Mat mask;
	//	cv::Mat loadBrush(int brushNumber);

	//};

	//class gridProperties{
	//	cv::Point2d gridCenter;
	//	int gridHalfSize;
	//	cv::Point2d gridOrientation;
	//    cv::Mat gridColor;
	//};
	


	void placeBrush(cv::Mat &Canvans, std::vector<myStroke> StrokeList, cv::Mat Segmentation);
	
	//// hertzman's method 
	//std::list<brushParams> getBrushParams(const cv::Mat img, const cv::Mat canvans, cv::Point2i gridSize);
 //   
	//void  randomPlace(cv::Mat &Canvans, int num_brushes);
//}