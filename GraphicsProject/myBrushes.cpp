#include "stdafx.h"
#include "myBrushes.h"
#include "utils.h"
using namespace std;
using namespace cv;
myBrushes::myBrushes(){

	const int numBrushes = 6;
	const char *  brushPath = "brush\\mask%d.png";
	for (int i = 0; i < numBrushes;i++){
		char imgpath[256];
		sprintf_s(imgpath, brushPath, i);
		cv::Mat mask = cv::imread(imgpath);
		
		if (!mask.data)
		{
			CString ImageName;
			ImageName.Format(_T("mask%d.png is NOT Found"), i);
			{
				AfxMessageBox(ImageName, MB_OK | MB_ICONSTOP);
			}
		}
		brushList.push_back(mask);
	}

}

void myBrushes::visMyBrushes(){
	for (int i = 0; i < brushList.size();i++)
	{
		char caption[256];
		sprintf_s(caption, "Brush %d", i+1);
		cv::namedWindow(caption, WINDOW_NORMAL|WINDOW_KEEPRATIO);
		cv::resizeWindow(caption, brushList.at(i).cols, brushList.at(i).rows);
		cv::moveWindow(caption, WindowPropertyDisplayBrush::ColOffset, (brushList.at(i).rows+WindowPropertyDisplayBrush:: RowOffset)*i);
		cv::imshow(caption, brushList.at(i));

	}

}