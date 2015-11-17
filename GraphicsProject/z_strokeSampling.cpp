#include "stdafx.h"
#include "z_strokeSampling.h"
using namespace cv;
std::vector<cv::Point2d> z_strokeSampling(Mat image){
	int gridSz = 20;
	int numStrokes = 200;
	Size inputImgSz = image.size();
	Size gridMapSz =  inputImgSz   / gridSz + Size(1, 1) ;


	Mat gridMap;
	resize(image, gridMap, gridMapSz);

	// convert to gray
	if (gridMap.channels() == 3)
	{
		cvtColor(gridMap, gridMap, cv::COLOR_BGR2GRAY);
	}


	//normalize to 0 to 1
	double valueSum = cv::sum(gridMap)[0];
	gridMap.convertTo(gridMap, CV_64FC1, 1.0 /valueSum );
	std::vector<cv::Point2d> strokePositions;
	for (int i = 0; i < inputImgSz.height; i += gridSz)
	{
		for (int j = 0; j<inputImgSz.width; j += gridSz){
			int   numStrokesGrid = (int)(gridMap.at<double>( ( i / gridSz),( j / gridSz))*numStrokes) + 4; // 20 20 grid at least should have 4 10 by 30 strokes ;
			for (int pts = 0; pts < numStrokesGrid; pts++){
				int px = int(rand() / (double)RAND_MAX  * gridSz) + i;;
				int py = int(rand() / (double)RAND_MAX  * gridSz)+ j;
				px = px>=inputImgSz.width ? inputImgSz.width - 1 : px;
				py = py>=inputImgSz.height ? inputImgSz.height - 1 : py;
				strokePositions.push_back(cv::Point2d(px, py));
			}
		}
	}
	return strokePositions;

}
