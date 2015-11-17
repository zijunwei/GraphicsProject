#ifndef _MYSTROKE_H__
#define _MYSTROKE_H__
#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/persistence.hpp>
#include "opencv2/imgproc.hpp"

class myStroke;

class myStroke
{
public:
	cv::Point2d stroke_location;
	double stroke_grad_orientation;
	double stroke_grad_magnitude;
	myStroke * neighbourStrokes;
protected:
private:
};


#endif