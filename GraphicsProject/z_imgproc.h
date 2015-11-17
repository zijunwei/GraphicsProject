#ifndef _Z_IMGPROC_H__
#define _Z_IMGPROC_H__
#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/persistence.hpp>
#include "opencv2/imgproc.hpp"


class imgStats
{
public: 
	cv::Mat grad_x;
	cv::Mat grad_y;
	cv::Mat grad_orientation;
	cv::Mat grad_magnitude;
	void imgStatsInit(cv::Mat inputImg);
protected:
private:
};
void getGradients(cv::Mat inputImg, cv::Mat &gradx, cv::Mat &grady,cv::Mat& ,cv::Mat&);

#endif