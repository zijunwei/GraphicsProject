#include "stdafx.h"
#include "StrokeProcessState.h"
#include "NUS.h"
#include "strokeProcess.h"
#include "vis.h"
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
	bool laterUpdate_graph = false,laterUpdate_size=false;
	if ( (curParam.mDensity!=prevParam.mDensity) || curParam.mNon_Uniformity!=prevParam.mNon_Uniformity ) //re-update the saliency sampling-> initial connection graph
	{
		NUS_Weibull(this->imgData->SaliencyImage, & (this->StrokeList), & (this->curParam));
		initStrokeOrientation(StrokeList, this->imgData->GradientOrientation);
		connectStrokeGraph(StrokeList, this->imgData->SegmentImage);
		initStrokeColor(StrokeList, this->imgData->OriginalImage);
		//Debug use ...Show Image
		vis_StrokePositions(this->imgData->OriginalImage, this->StrokeList);
		laterUpdate_graph = true;
	}
	if (curParam.mCoarseness!=prevParam.mCoarseness || laterUpdate_graph)  // reinitialize the size 
	{
		initStrokeSize(this->imgData->SaliencyImage, (this->StrokeList),  this->curParam.mCoarseness);
		laterUpdate_size = true;
	}
	if (curParam.mLocal_Iostropy != prevParam.mLocal_Iostropy || laterUpdate_graph) // update connection graph
	{
		updateOrientation(this->StrokeList, this->curParam.mLocal_Iostropy);
		connectStrokeGraph(StrokeList, this->imgData->SegmentImage);
		laterUpdate_graph = true;
	}
	if (curParam.mSize_Contrast!=prevParam.mSize_Contrast || laterUpdate_graph || laterUpdate_size) //update size 
	{
		updateSize(StrokeList, this->curParam.mSize_Contrast);
	}

	if (curParam.mHue_Constrast != prevParam.mHue_Constrast ||laterUpdate_graph ) //update the three color channels separately
	{

	}

	if (curParam.mLightness_Contrast != prevParam.mLightness_Contrast ||laterUpdate_graph) //update the three color channels separately
	{
	}

	if (curParam.mChroma_Constrast != prevParam.mChroma_Constrast ||laterUpdate_graph) //update the three color channels separately
	{
	}



}
