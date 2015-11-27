#ifndef VIS_H_
#define VIS_H_
#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/persistence.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "myStroke.h"
#include <vector>
void vis_StrokePositions(cv::Mat inputImage, std::vector<cv::Point2i> strokePositions);
cv::Mat vis_StrokeAll(cv::Mat inputImage, std::vector<myStroke> myStrokes);
#endif