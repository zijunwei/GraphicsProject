
#ifndef STROKE_PROCESS_H
#define STROKE_PROCESS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "myStroke.h"
void connectStrokeGraph(std::vector <myStroke> & StrokeList, cv::Mat segMask);
void initStrokeOrientation(std::vector<myStroke>& StrokeList, cv::Mat salImg);
void initStrokeColor(std::vector <myStroke> & StrokeList, cv::Mat refImg);
void initStrokeSize(std::vector<myStroke> &,cv::Mat );


void updateOrientation(std::vector<myStroke> & myStrokes);
void updateSize(std::vector<myStroke> & myStrokes);
void updateColor(std::vector<myStroke> & myStrokes);

#endif /* defined(STROKE_PROCESS_H) */