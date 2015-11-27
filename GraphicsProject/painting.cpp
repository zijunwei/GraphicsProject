#include "stdafx.h"
#include "painting.h"
#include "utils.h"
#include "colorspace.h"
#include "myBrushes.h"
#include <stdio.h>

//const int numBrushes = 6;
//const char *  brushPath = "brush\\mask%d.png";
//cv::Mat painting::brushParams::loadBrush(int brushNumber){
//
//	char imgpath[256];
//	sprintf_s(imgpath, brushPath, brushNumber);
//	cv::Mat mask = cv::imread(imgpath);
//	
//	if (DEBUGSHOW){
//		//cv::namedWindow("brush display window");              // Create a window for display.
//		cv::imshow("Display window", mask);                   // Show our image inside it.
//		//cv::waitKey(0);                                       // Wait for a keystroke in the window
//	
//	}
//
//	// resize to a small size:
//
//	cv::resize(mask, mask, cv::Size(W, H));
//	return mask;
//
//		
//}
//
//void painting::randomPlace(cv::Mat &Canvans, int num_brushes){
//
//	for (int i = 0; i < num_brushes; i++){
//	
//		// generate random brushes 
//		//place them on Canvans
//	
//	}
//
//
//}

void placeBrush(cv::Mat &Canvans, std::vector<myStroke> StrokeList)
{
	myBrushes brushes;

	for (int i = 0; i < StrokeList.size();i++)
	{
		myStroke *curStroke = &StrokeList.at(i);

		//load the random brush from 6 brushes
		float r = (float)rand() / (float)RAND_MAX;
		int   randBrushNo = (int )((float)rand() / (float)RAND_MAX * 5);
		cv::Mat brushModel = brushes.brushList.at(randBrushNo);

		//add color:
		double B, G, R;
		Lch2Rgb(&R, &G, &B, curStroke->lchColor(0), curStroke->lchColor(1), curStroke->lchColor(2)*180/PI);
		cv::Vec3b bgrColor((int)(B*255), (int) (G*255),(int)(R*255));
		


		//change size:
		if (curStroke->strokeSize(0)<1)
		{
			curStroke->strokeSize(0) = 30;
		}
		if (curStroke->strokeSize(1) < 1)
		{
			curStroke->strokeSize(1) = 10;
		}

		cv::resize(brushModel, brushModel, cv::Size((int)(curStroke->strokeSize(1)), (int)(curStroke->strokeSize(0))));


		//rotate by an angle:
		cv::Point2i brushCenter((int)brushModel.cols / 2, (int)brushModel.rows / 2);
		cv::Mat rot = cv::getRotationMatrix2D(brushCenter, curStroke->stroke_grad_orientation * 180 / PI, 1.0);

		cv::Rect bbox = cv::RotatedRect(brushCenter, brushModel.size(), curStroke->stroke_grad_orientation * 180 / PI).boundingRect();

		rot.at<double>(0, 2) += bbox.width / 2.0 - brushCenter.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - brushCenter.y;

		cv::warpAffine(brushModel, brushModel, rot, bbox.size());
		//fill in color
		for (int i = 0; i < brushModel.cols; i++)
		{
			for (int j = 0; j < brushModel.rows; j++)
			{
				if (brushModel.at<cv::Vec3b>(j, i) != cv::Vec3b(0, 0, 0))
				{
					brushModel.at<cv::Vec3b>(j, i) = bgrColor;
				}
			}
		}




		//place the brush model on a place:

		brushCenter.x =(int) brushModel.cols / 2;
		brushCenter.y = (int)brushModel.rows / 2;
		double blend_ratio = 0.5;

		cv::Point2i CanvansLocation = curStroke->stroke_location;
		for (int i = 0; i < brushModel.cols; i++){
			for (int j = 0; j < brushModel.rows;j++)
		   { 
		          if (brushModel.at<cv::Vec3b>(j,i) !=cv::Vec3b(0,0,0))
		          {
					  if (CanvansLocation.x - brushCenter.x + i >= 0 && CanvansLocation.y - brushCenter.y + j >= 0 &&
						  CanvansLocation.x - brushCenter.x + i<Canvans.cols &&CanvansLocation.y - brushCenter.y + j <Canvans.rows)
					  {
						  Canvans.at<cv::Vec3b>(CanvansLocation.y - brushCenter.y + j, CanvansLocation.x - brushCenter.x + i) =
							  blend_ratio* Canvans.at<cv::Vec3b>(CanvansLocation.y - brushCenter.y + j, CanvansLocation.x - brushCenter.x + i)
							  +(1-blend_ratio) *brushModel.at<cv::Vec3b>(j, i);
					  }
		          }
		   }
		}
		

	}

}
