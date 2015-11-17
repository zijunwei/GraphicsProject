#include "stdafx.h"
#include "math.h"
#include "z_imgproc.h"
using namespace cv;

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