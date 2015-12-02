#ifndef _MYBRUSH_H__
#define _MYBRUSH_H__
#include "opencv2\opencv.hpp"
#include <opencv2\core\persistence.hpp>
#include "opencv2\imgproc.hpp"
#include "opencv2\imgproc\imgproc.hpp"

#include <vector>

class myBrushes
{
public:

	myBrushes();
	std::vector<cv::Mat> brushList;
	void visMyBrushes();
protected:
private:
};


#endif