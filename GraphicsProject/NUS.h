#ifndef  NUS_H
#define  NUS_H

#include <opencv2/core.hpp>
#include "myStroke.h"
#include <vector>
#include "ParamBox.h"
void NUS_Weibull(cv::Mat SaliencyImage, std::vector<myStroke> *StrokeList, double ,double );

#endif // !NUS_H
