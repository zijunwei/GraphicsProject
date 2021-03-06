#ifndef _MYSTROKE_H__
#define _MYSTROKE_H__
#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/persistence.hpp>
#include "opencv2/imgproc.hpp"


class myStroke
{
public:

	// Don't directly use default constructors
	myStroke();
	//cv::Point2d stroke_grad;
	cv::Point2i StrokeLocation;
	double GradientOrientation;
	//cv::Vec3b rgbColor; // uint8 format BGR
	cv::Vec3d lchColor;
	double ColorLightness;
	double ColorChroma;
	double ColorHue;
	cv::Vec2f StrokeScale;
	// neighbor strokes in 4 quadrants.
	myStroke * NeiStrokeQ1;
	myStroke * NeiStrokeQ2;
	myStroke * NeiStrokeQ3;
	myStroke * NeiStrokeQ4;
	//double getGradMag();

protected:
private:
};


#endif