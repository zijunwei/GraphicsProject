#include "stdafx.h"
#include "myBrushes.h"

using namespace std;
using namespace cv;
myBrushes::myBrushes(){

	const int numBrushes = 6;
	const char *  brushPath = "brush\\mask%d.png";
	for (int i = 0; i < numBrushes;i++){
		char imgpath[256];
		sprintf_s(imgpath, brushPath, i);
		//cv::Mat mask = cv::imread(imgpath);
		cv::Mat mask = cv::imread(imgpath);

		//cvtColor(mask, mask, CV_RGB2GRAY);
		brushList.push_back(mask);
	}

}

void myBrushes::visBrushes(){
	for (int i = 0; i < brushList.size();i++)
	{
		char caption[256];
		sprintf_s(caption, "mask%d", i);

		cv::namedWindow(caption, 0);
		cv::imshow(caption, brushList.at(i));

	}

}