#include "stdafx.h"
#include "z_Saliency.h"
using namespace cv;
bool z_Saliency(cv::InputArray image, cv::OutputArray saliencyMap){

	
		cv::Mat grayTemp, grayDown;
		std::vector<Mat> mv;
		int resImWidth = 64;
		int resImHeight = 64;
		cv::Size resizedImageSize(resImWidth, resImHeight);

		cv::Mat realImage(resizedImageSize, CV_64F);
		Mat imaginaryImage(resizedImageSize, CV_64F);
		imaginaryImage.setTo(0);
		Mat combinedImage(resizedImageSize, CV_64FC2);
		Mat imageDFT;
		Mat logAmplitude;
		Mat angle(resizedImageSize, CV_64F);
		Mat magnitude(resizedImageSize, CV_64F);
		Mat logAmplitude_blur, imageGR;

		if (image.channels() == 3)
		{
			cvtColor(image, imageGR, COLOR_BGR2GRAY);
			resize(imageGR, grayDown, resizedImageSize, 0, 0, INTER_LINEAR);
		}
		else
		{
			resize(image, grayDown, resizedImageSize, 0, 0, INTER_LINEAR);
		}

		grayDown.convertTo(realImage, CV_64F);

		mv.push_back(realImage);
		mv.push_back(imaginaryImage);
		merge(mv, combinedImage);
		dft(combinedImage, imageDFT);
		split(imageDFT, mv);

		//-- Get magnitude and phase of frequency spectrum --//
		cartToPolar(mv.at(0), mv.at(1), magnitude, angle, false);
		log(magnitude, logAmplitude);
		//-- Blur log amplitude with averaging filter --//
		blur(logAmplitude, logAmplitude_blur, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);

		exp(logAmplitude - logAmplitude_blur, magnitude);
		//-- Back to cartesian frequency domain --//
		polarToCart(magnitude, angle, mv.at(0), mv.at(1), false);
		merge(mv, imageDFT);
		dft(imageDFT, combinedImage, DFT_INVERSE);
		split(combinedImage, mv);

		cartToPolar(mv.at(0), mv.at(1), magnitude, angle, false);
		GaussianBlur(magnitude, magnitude, Size(5, 5), 8, 0, BORDER_DEFAULT);
		magnitude = magnitude.mul(magnitude);

		double minVal, maxVal;
		minMaxLoc(magnitude, &minVal, &maxVal);

		magnitude = magnitude / maxVal;
		magnitude.convertTo(magnitude, CV_32F);

		resize(magnitude, saliencyMap, image.size(), 0, 0, cv::INTER_LINEAR);



		return true;

	

}

