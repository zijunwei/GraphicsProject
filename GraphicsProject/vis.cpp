#include "stdafx.h"
#include "vis.h"
#include "utils.h"
#include "mygl_ShowImage.h"
// draw stroke points only
void vis_StrokePositions(cv::Mat inputImages, std::vector<myStroke> StrokeList){
	cv::Mat outputImg = inputImages.clone();
	for (int i = 0; i < StrokeList.size(); i++){
		cv::circle(outputImg, StrokeList.at(i).StrokeLocation, 2, 255);
	}
	if (USE_OPENGL){
		cv::namedWindow("stroke placement", 0);
		cv::imshow("stroke placement", outputImg);
	}
	else{
		mygl_ShowImage::upDate(outputImg);
		
	}

}


// draw strokes and relations
cv::Mat vis_StrokeAll(cv::Mat inputImage, std::vector<myStroke> myStrokes){
	cv::Mat Canvas = inputImage.clone();
	//Canvas.setTo(cv::Scalar::all(255));
	for (int i = 0; i < myStrokes.size(); i++){
		//draw the point out...
		cv::circle(Canvas,myStrokes.at(i).StrokeLocation,2,cv::Scalar::all(0));
		// draw the connecting points out
		if (myStrokes.at(i).NeiStrokeQ1)
		{
			cv::arrowedLine(Canvas, myStrokes.at(i).StrokeLocation, myStrokes.at(i).NeiStrokeQ1->StrokeLocation, cv::Scalar::all(255));
		}
		if (myStrokes.at(i).NeiStrokeQ2)
		{
			cv::arrowedLine(Canvas, myStrokes.at(i).StrokeLocation, myStrokes.at(i).NeiStrokeQ2->StrokeLocation, cv::Scalar::all(255));
		}
		if (myStrokes.at(i).NeiStrokeQ3)
		{
			cv::arrowedLine(Canvas, myStrokes.at(i).StrokeLocation, myStrokes.at(i).NeiStrokeQ3->StrokeLocation, cv::Scalar::all(255));
		}
		if (myStrokes.at(i).NeiStrokeQ4)
		{
			cv::arrowedLine(Canvas, myStrokes.at(i).StrokeLocation, myStrokes.at(i).NeiStrokeQ4->StrokeLocation, cv::Scalar::all(255));
		}
	
	}

	if (USE_OPENGL)
	{
		return Canvas;
	}
	else
	{
		mygl_ShowImage::upDate(Canvas);
		return Canvas;
	}

}
