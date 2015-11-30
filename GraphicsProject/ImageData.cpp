#include "stdafx.h"
#include "ImageData.h"
#include "SLIC_superpixels.h"
#include "computeSaliency.h"
#include "utils.h"
ImageData::ImageData()
{
}


ImageData::~ImageData()
{
}

BOOL ImageData::setOriginalImage(cv::Mat inputImage)
{
	this->OriginalImage = inputImage.clone();
	if (this->OriginalImage.channels()!=3)
	{
		return FALSE;
	}

	//Segment image 
	SLICSuperpixel slic(OriginalImage, NUMBER_OF_SUPERPIXELS);
	slic.generateSuperPixels();
	this->SegmentImage = slic.getClustersIndex();
	this->SegmentImage_color = slic.recolor();
	
	//Saliency image:
	computeSaliency(this->OriginalImage, this->SaliencyImage);

	//Compute Gradient orientation and Gradient ratio
	computeGraidentOrientation(this->OriginalImage, this->GradientOrientation, this->GradientRatio);
	return TRUE;


}
