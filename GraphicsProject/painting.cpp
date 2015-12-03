#include "stdafx.h"
#include "painting.h"
#include "utils.h"
#include "colorspace.h"
#include "myBrushes.h"
#include <stdio.h>



void placeBrush(cv::Mat &Canvans, std::vector<myStroke> StrokeList, cv::Mat Segmentation)
{
	myBrushes brushes;

	for (int i = StrokeList.size()-1;i>=0; i--)
	{
		myStroke *curStroke = &StrokeList.at(i);

		//load the random brush from 6 brushes
		float r = (float)rand() / (float)RAND_MAX;
		int   randBrushNo = (int )((float)rand() / (float)RAND_MAX * 5);
		cv::Mat brushModel = brushes.brushList.at(randBrushNo);

		//add color:
		double B, G, R;
		Lch2Rgb(&R, &G, &B, curStroke->ColorLightness, curStroke->ColorChroma, curStroke->ColorHue*180/PI);
		cv::Vec3b bgrColor((int)(B*255), (int) (G*255),(int)(R*255));
		


		////change size:
		if (curStroke->StrokeScale(0) < 1)
		{
			curStroke->StrokeScale(0) = 1;
		}
		if (curStroke->StrokeScale(1) < 1)
		{
			curStroke->StrokeScale(1) = 1;
		}

		cv::resize(brushModel, brushModel, cv::Size((int)(curStroke->StrokeScale(1)*Coarseness::minSize), (int)(curStroke->StrokeScale(0)*Coarseness::minSize )));


		//rotate by an angle:
		cv::Point2i brushCenter((int)brushModel.cols / 2, (int)brushModel.rows / 2);
		cv::Mat rot = cv::getRotationMatrix2D(brushCenter, curStroke->GradientOrientation * 180 / PI-90, 1.0);

		cv::Rect bbox = cv::RotatedRect(brushCenter, brushModel.size(),(float) (curStroke->GradientOrientation * 180 / PI-90)).boundingRect();

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
		double blend_ratio = 0.2;

		cv::Point2i CanvansLocation = curStroke->StrokeLocation;
		int SegRegion = Segmentation.at<int>(CanvansLocation.y, CanvansLocation.x);
		for (int i = 0; i < brushModel.cols; i++){
			for (int j = 0; j < brushModel.rows;j++)
		   { 
		          if (brushModel.at<cv::Vec3b>(j,i) !=cv::Vec3b(0,0,0))
		          {
					  if (CanvansLocation.x - brushCenter.x + i >= 0 && CanvansLocation.y - brushCenter.y + j >= 0 &&
						  CanvansLocation.x - brushCenter.x + i<Canvans.cols &&CanvansLocation.y - brushCenter.y + j <Canvans.rows  
						  && Segmentation.at<int>(CanvansLocation.y - brushCenter.y + j, CanvansLocation.x - brushCenter.x + i)<=SegRegion+1 &&
						  Segmentation.at<int>(CanvansLocation.y - brushCenter.y + j, CanvansLocation.x - brushCenter.x + i) > SegRegion - 1)
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
