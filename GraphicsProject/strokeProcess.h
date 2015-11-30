
#ifndef STROKE_PROCESS_H
#define STROKE_PROCESS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "myStroke.h"
void connectStrokeGraph(std::vector <myStroke> & StrokeList, cv::Mat segMask);
void initStrokeOrientation(std::vector<myStroke>& StrokeList, const cv::Mat & GradImage);
void initStrokeColor(std::vector <myStroke> & StrokeList, cv::Mat refImg);
void initStrokeSize(const cv::Mat & , const cv::Mat &,  std::vector<myStroke> & , double  );


void updateOrientation(std::vector<myStroke> & myStrokes,double);
void updateSize(std::vector<myStroke> & myStrokes,double);

//split it into 3 components individually
void updateColor(std::vector<myStroke> & myStrokes,double);

void updateLightness(std::vector<myStroke> & myStrokes, double);
void updateChroma(std::vector<myStroke> & myStrokes, double);
void updateHue(std::vector<myStroke> & myStrokes, double);


#endif /* defined(STROKE_PROCESS_H) */