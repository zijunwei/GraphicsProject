#include "stdafx.h"
#include "utils.h"
#include "opencv2/highgui.hpp"
#include "mygl_ShowImage.h"
//#include "opencv2/imgproc.hpp"
double cvtRange(int barVal, double Scale, double Offset)
{
	return   Scale*((double)barVal) + Offset;
}

void ShowSingleImage(const char *caption, const cv::Mat inputImage, const int colOffset, const int rowOffset){
	if (USE_OPENGL)
	{
		cv::namedWindow(caption, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
		cv::resizeWindow(caption, inputImage.cols, inputImage.rows);
		cv::moveWindow(caption, colOffset, rowOffset);
		cv::imshow(caption, inputImage);
	}
	else
	{
		mygl_ShowImage::upDate(inputImage);
	}


}