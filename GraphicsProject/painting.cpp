#include "stdafx.h"
#include "painting.h"
#include <stdio.h>

const int numBrushes = 6;
const char *  brushPath = "brush\\mask%d.png";
cv::Mat painting::brushParams::loadBrush(int brushNumber){

	char imgpath[256];
	sprintf_s(imgpath, brushPath, brushNumber);
	cv::Mat mask = cv::imread(imgpath);
	
	if (DEBUGSHOW){
		//cv::namedWindow("brush display window");              // Create a window for display.
		cv::imshow("Display window", mask);                   // Show our image inside it.
		//cv::waitKey(0);                                       // Wait for a keystroke in the window
	
	}

	// resize to a small size:

	cv::resize(mask, mask, cv::Size(W, H));
	return mask;

		
}

void painting::randomPlace(cv::Mat &Canvans, int num_brushes){

	for (int i = 0; i < num_brushes; i++){
	
		// generate random brushes 
		//place them on Canvans
	
	}


}