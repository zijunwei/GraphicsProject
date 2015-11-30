#pragma once
#include <opencv2/core.hpp>
class ImageData
{
public:
	ImageData();
	~ImageData();
	BOOL setOriginalImage(cv::Mat );
public :
	cv::Mat OriginalImage;
	cv::Mat SaliencyImage;
	cv::Mat SegmentImage;
	cv::Mat SegmentImage_color;
	cv::Mat GradientOrientation;
	cv::Mat GradientRatio;  // Gradient Dx/Dy
};

