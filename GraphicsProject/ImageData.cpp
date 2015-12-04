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
	slic.recolor2(this->OriginalImage,this->SegmentImage_color);
	
	//Saliency image:
	computeSaliency(this->OriginalImage, this->SaliencyImage);

	//Compute Gradient orientation and Gradient ratio
	computeGraidentOrientation(this->OriginalImage, this->GradientOrientation, this->GradientRatio);
	return TRUE;


}


void ImageData::visImageData()
{
	
	ShowSingleImage(WindowPropertyDisplayImage::CaptionOriginalImage, this->OriginalImage,
		WindowPropertyDisplayImage::ColOffset,WindowPropertyDisplayImage::RowOffset);
	//ShowSingleImage(WindowPropertyDisplayImage::CaptionSaliencyImage, this->SaliencyImage,
	//	WindowPropertyDisplayImage::ColOffset, WindowPropertyDisplayImage::RowOffset*2+this->OriginalImage.rows);
	//ShowSingleImage(WindowPropertyDisplayImage::CaptionSegmentationImage, this->SegmentImage_color,
	//	WindowPropertyDisplayImage::ColOffset, WindowPropertyDisplayImage::RowOffset*3 + this->OriginalImage.rows + this->SaliencyImage.rows);

	
}

