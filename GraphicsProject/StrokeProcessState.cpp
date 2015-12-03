#include "stdafx.h"
#include "StrokeProcessState.h"
#include "NUS.h"
#include "strokeProcess.h"
#include "vis.h"
#include "utils.h"
#include "painting.h"
StrokeProcessState::StrokeProcessState()
{
	this->curParam = ParamBox(-1, -1, -1, -1, -1, -1, -1, -1);
	
}


StrokeProcessState::~StrokeProcessState()
{
}

void StrokeProcessState::updateState(ParamBox input)
{
	this->prevParam = curParam;
	this->curParam = input;
	//Compare the difference between curParam and prevParam, then update according to the changes
	
	if (this->StrokeList.empty())
	{		NUS_Weibull(this->imgData->SaliencyImage, & (this->StrokeList), this->curParam.mDensity,this->curParam.mNon_Uniformity);

	}

	if (laterUpdate_graph) //re-update the saliency sampling-> initial connection graph
	{
		//NUS_Weibull(this->imgData->SaliencyImage, & (this->StrokeList), this->curParam.mDensity,this->curParam.mNon_Uniformity);
		initStrokeOrientation(StrokeList, this->imgData->GradientOrientation);
		connectStrokeGraph(StrokeList, this->imgData->SegmentImage);
		//Debug use ...Show Image
		//vis_StrokePositions(this->imgData->OriginalImage, this->StrokeList);
		
	}
	
	if (curParam.mLocal_Iostropy != prevParam.mLocal_Iostropy || laterUpdate_graph) // update connection graph
	{
		updateOrientation(this->StrokeList, this->curParam.mLocal_Iostropy);
		connectStrokeGraph(StrokeList, this->imgData->SegmentImage);
		laterUpdate_graph = true;
	}
	if (curParam.mCoarseness != prevParam.mCoarseness || laterUpdate_graph)  // reinitialize the size 
	{
		initStrokeSize(this->imgData->SaliencyImage, this->imgData->GradientRatio, (this->StrokeList), this->curParam.mCoarseness);
		laterUpdate_size = true;
	}
	if (curParam.mSize_Contrast!=prevParam.mSize_Contrast || laterUpdate_graph || laterUpdate_size) //update size 
	{
		updateSize(StrokeList, this->curParam.mSize_Contrast);
	}

	if (laterUpdate_graph || laterUpdate_size)
	{
		initStrokeColor(StrokeList, this->imgData->OriginalImage);   

	}

	if (curParam.mHue_Constrast != prevParam.mHue_Constrast ||laterUpdate_graph ) //update the three color channels separately
	{  
		updateHue(StrokeList,curParam.mHue_Constrast);
	}

	if (curParam.mLightness_Contrast != prevParam.mLightness_Contrast ||laterUpdate_graph) //update the three color channels separately
	{
		updateLightness(StrokeList, curParam.mLightness_Contrast);
	}

	if (curParam.mChroma_Constrast != prevParam.mChroma_Constrast ||laterUpdate_graph) //update the three color channels separately
	{
		updateChroma(StrokeList, curParam.mChroma_Constrast);
	}



}

void StrokeProcessState::clearStrokeList()
{
	if (! this->StrokeList.empty())
	{
		this->StrokeList.clear();
	}
}

void StrokeProcessState::visStrokePosition()
{
	cv::Mat outputImg = this->imgData->OriginalImage.clone();
	for (int i = 0; i < StrokeList.size(); i++){
		cv::circle(outputImg, StrokeList.at(i).StrokeLocation, 1, cv::Scalar(0,0,255),3);
	}
	ShowSingleImage(WindowsPropertyRsltImage::CaptionStrokePositions, outputImg, WindowsPropertyRsltImage::ColOffset, WindowsPropertyRsltImage::RowOffset);
}

void StrokeProcessState::visFinalResults()
{
	cv::Mat PaintedImage = this->imgData->OriginalImage.clone();
	placeBrush(PaintedImage,this->StrokeList, this->imgData->SegmentImage);
	cv::resize(PaintedImage, PaintedImage, PaintedImage.size()*2);
	ShowSingleImage(WindowsPropertyRsltImage::CaptionRstl, PaintedImage, WindowsPropertyRsltImage::ColOffset,
		WindowsPropertyRsltImage::RowOffset+PaintedImage.rows);
	laterUpdate_graph = false;
	laterUpdate_size = false;
}

void StrokeProcessState::updatePramsOnly(ParamBox newParam)
{
	this->prevParam = this->curParam;
	this->curParam = newParam;
	laterUpdate_graph = true;
}
