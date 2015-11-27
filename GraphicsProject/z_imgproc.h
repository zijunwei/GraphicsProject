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
	cv::Mat grad_orientation_in_degree; // degree of gradient orientation in range [0 ~ 2pi]
	cv::Mat curImg;
	imgStats();
	imgStats(cv::Mat inputImg);
	void getGradients(void);
	void getGradOrientationInDegree();
protected:
private:

};


#endif