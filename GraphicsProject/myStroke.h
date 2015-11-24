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
	cv::Point2i stroke_location;
	double stroke_grad_orientation;
	double stroke_grad_magnitude;
	cv::Vec3d rgbColor;
	cv::Vec2d strokeSize;
	// neighbor strokes in 4 qudratants.
	myStroke * NeiStrokeQ1;
	myStroke * NeiStrokeQ2;
	myStroke * NeiStrokeQ3;
	myStroke * NeiStrokeQ4;


protected:
private:
};


#endif