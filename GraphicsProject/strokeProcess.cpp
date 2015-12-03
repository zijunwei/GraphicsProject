#include "stdafx.h"
#include "strokeProcess.h"
#include "colorspace.h"
#include "utils.h"

#define epsilon 0.001

//Make sure two things:
using namespace cv;
void connectStrokeGraph(std::vector <myStroke> & StrokeList, cv::Mat segMask){

	//Initializing Neighbors
	//cv::cvtColor(segMask, segMask, CV_RGB2GRAY);
	for (int i = 0; i < StrokeList.size(); i++){

		double dist1 = INFINITY, dist2 = INFINITY, dist3 = INFINITY, dist4 = INFINITY;
		myStroke * curStroke = &StrokeList.at(i);
		curStroke->NeiStrokeQ1 = NULL;
		curStroke->NeiStrokeQ2 = NULL;
		curStroke->NeiStrokeQ3 = NULL;
		curStroke->NeiStrokeQ4 = NULL;

		for (int j = 0; j < StrokeList.size(); j++){
			if (j == i){
				continue;
			}

			double difx = StrokeList.at(j).StrokeLocation.x - curStroke->StrokeLocation.x;
			double dify = StrokeList.at(j).StrokeLocation.y - curStroke->StrokeLocation.y;
			//double dist = sqrt(pow(difx, 2) + pow(dify, 2));
			//// now decide which Quadrant current method within

			//double x = 1;
			//double y = curStroke->stroke_grad_orientation;
			//double projLength = sqrt(pow(x, 2) + pow(y, 2));
			double rectified_dif_x = (difx * cos(curStroke->GradientOrientation) + dify*sin(curStroke->GradientOrientation));
			double rectified_dif_y = (difx*(-sin(curStroke->GradientOrientation)) + dify*cos(curStroke->GradientOrientation));
			double rectified_dist = sqrt(pow(rectified_dif_x, 2) + pow(rectified_dif_y, 2));
			// selected different quadrant:
			// q1
			if (rectified_dif_x >= 0 && rectified_dif_y >= 0 && rectified_dist < dist1)
			{
				dist1 = rectified_dist;
				curStroke->NeiStrokeQ1 = &StrokeList.at(j);
				continue;
			}
			//q2
			if (rectified_dif_x<0 && rectified_dif_y > 0 && rectified_dist < dist2)
			{
				dist2 = rectified_dist;
				curStroke->NeiStrokeQ2 = &StrokeList.at(j);
				continue;
			}
			//q3
			if (rectified_dif_x < 0 && rectified_dif_y < 0 && rectified_dist < dist3)
			{
				dist3 = rectified_dist;
				curStroke->NeiStrokeQ3 = &StrokeList.at(j);
				continue;
			}
			//q4
			if (rectified_dif_x > 0 && rectified_dif_y < 0 && rectified_dist < dist4)
			{
				dist4 = rectified_dist;
				curStroke->NeiStrokeQ4 = &StrokeList.at(j);
				continue;
			}

		}

	}

	//Clean up the neighbors that are not in the same regions or distance too large
	for (int i = 0; i < StrokeList.size(); i++){

		myStroke * curStroke = &StrokeList.at(i);

		if (curStroke->NeiStrokeQ1 && (segMask.at<int>(curStroke->StrokeLocation.y, curStroke->StrokeLocation.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ1->StrokeLocation.y, curStroke->NeiStrokeQ1->StrokeLocation.x)
			|| cv::norm(curStroke->StrokeLocation - curStroke->NeiStrokeQ1->StrokeLocation) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ1 = NULL;
		}
		if (curStroke->NeiStrokeQ2 && (segMask.at<int>(curStroke->StrokeLocation.y, curStroke->StrokeLocation.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ2->StrokeLocation.y, curStroke->NeiStrokeQ2->StrokeLocation.x)
			|| cv::norm(curStroke->StrokeLocation - curStroke->NeiStrokeQ2->StrokeLocation) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ2 = NULL;
		}
		if (curStroke->NeiStrokeQ3 && (segMask.at<int>(curStroke->StrokeLocation.y, curStroke->StrokeLocation.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ3->StrokeLocation.y, curStroke->NeiStrokeQ3->StrokeLocation.x)
			|| cv::norm(curStroke->StrokeLocation - curStroke->NeiStrokeQ3->StrokeLocation) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ3 = NULL;
		}
		if (curStroke->NeiStrokeQ4 && (segMask.at<int>(curStroke->StrokeLocation.y, curStroke->StrokeLocation.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ4->StrokeLocation.y, curStroke->NeiStrokeQ4->StrokeLocation.x)
			|| cv::norm(curStroke->StrokeLocation - curStroke->NeiStrokeQ4->StrokeLocation) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ4 = NULL;
		}
	}
} //end of connectStrokeGraph




void initStrokeSize(const cv::Mat  & saliencyImage, const cv::Mat & gradientRatio, std::vector<myStroke> & StrokeList, double mCoarseness)
{
	float minSaliency = 100;
	float maxSaliency = 0;
	//for debug use, try to find max saliency.

	//first of all decide the minimal size would be (10,30);
	for (int i = 0; i < StrokeList.size(); i++)
	{
		float unitSaliency = saliencyImage.at<float>(StrokeList.at(i).StrokeLocation.y, StrokeList.at(i).StrokeLocation.x);
		if ((unitSaliency) < minSaliency)
		{
			minSaliency = (unitSaliency);
		}
		if (unitSaliency>maxSaliency)
		{
			maxSaliency = unitSaliency;
		}
	}


	maxSaliency = pow(maxSaliency, 0.5);
	for (int i = 0; i < StrokeList.size(); i++)
	{


		double curSaliency = (double)saliencyImage.at<float>(StrokeList.at(i).StrokeLocation.y, StrokeList.at(i).StrokeLocation.x);

		curSaliency = pow(curSaliency, 0.5);

		double dx = 1;
		double dy = 4;
		dx *= maxSaliency / curSaliency;
		dy *= maxSaliency / curSaliency;
		//Set the constraint
		if (dx > Coarseness::maxScale) { dx = Coarseness::maxScale; }
		if (dy > Coarseness::maxScale) { dy = Coarseness::maxScale; }

		float x = (float)dx;
		float y = (float)dy;
		StrokeList.at(i).StrokeScale = cv::Vec2f(x, y)*mCoarseness;
	}
	//Debug to find the max and min
	minSaliency = 0;
}




void initStrokeColor(std::vector <myStroke> & StrokeList, cv::Mat refImg){
	for (int i = 0; i < StrokeList.size(); i++)
	{
		//StrokeList.at(i).rgbColor = refImg.at<cv::Vec3b>(StrokeList.at(i).stroke_location.y, StrokeList.at(i).stroke_location.x);
		cv::Vec3d tmpBGR = refImg.at<cv::Vec3b>(StrokeList.at(i).StrokeLocation.y, StrokeList.at(i).StrokeLocation.x);
		tmpBGR = tmpBGR / 255.0;
		double L, C, H;
		Rgb2Lch(&L, &C, &H, tmpBGR(2), tmpBGR(1), tmpBGR(0));

		StrokeList.at(i).ColorLightness = L;
		StrokeList.at(i).ColorChroma = C;
		StrokeList.at(i).ColorHue = H / 180 * PI;



	}

}

void initStrokeOrientation(std::vector<myStroke>& StrokeList, const cv::Mat  &GradImage)
{//todo this is used to move everything about initializing point locations here
	for (int i = 0; i < StrokeList.size(); i++)
	{
		StrokeList.at(i).GradientOrientation =
			GradImage.at<double>(StrokeList.at(i).StrokeLocation.y, StrokeList.at(i).StrokeLocation.x);
	}
}




void updateOrientation(std::vector<myStroke> & myStrokes, double mLocal_Iostropy){

	std::vector<myStroke>srcStrokes = myStrokes;
	std::vector<myStroke>refStrokes = myStrokes;
	for (int i = 0; i < N_ITERATION; i++){
		for (int n = 0; n < myStrokes.size(); n++){


			//step 1 compute D(theta)
			double D_theta = 0;
			if (myStrokes.at(n).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - refStrokes.at(n).NeiStrokeQ1->StrokeLocation);
				double diff_angle = sin(refStrokes.at(n).NeiStrokeQ1->GradientOrientation - myStrokes.at(n).GradientOrientation);
				D_theta += 1 / dist * diff_angle;
			}
			if (myStrokes.at(n).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - refStrokes.at(n).NeiStrokeQ2->StrokeLocation);
				double diff_angle = sin(refStrokes.at(n).NeiStrokeQ2->GradientOrientation - myStrokes.at(n).GradientOrientation);
				D_theta += 1 / dist * diff_angle;
			}
			if (myStrokes.at(n).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - refStrokes.at(n).NeiStrokeQ3->StrokeLocation);
				double diff_angle = sin(refStrokes.at(n).NeiStrokeQ3->GradientOrientation - myStrokes.at(n).GradientOrientation);
				D_theta += 1 / dist * diff_angle;
			}
			if (myStrokes.at(n).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - refStrokes.at(n).NeiStrokeQ4->StrokeLocation);
				double diff_angle = sin(refStrokes.at(n).NeiStrokeQ4->GradientOrientation - myStrokes.at(n).GradientOrientation);
				D_theta += 1 / dist * diff_angle;
			}

			double R_theta = sin(srcStrokes.at(n).GradientOrientation - myStrokes.at(n).GradientOrientation);

			double random_num = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);


			myStrokes.at(n).GradientOrientation = myStrokes.at(n).GradientOrientation + R_theta + mLocal_Iostropy * D_theta + RANDOM_RANGE* random_num;
		}
		refStrokes = myStrokes;
	}




}

void updateSize(std::vector<myStroke> & myStrokes, double mSizeContrast)
{
	std::vector<myStroke>  refStrokes = myStrokes;
	for (int iStroke = 0; iStroke < myStrokes.size(); iStroke++){
		for (int iter = 0; iter < N_ITERATION; iter++){

			double D_sx = 0;
			double D_sy = 0;
			if (myStrokes.at(iStroke).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(iStroke).StrokeLocation - myStrokes.at(iStroke).NeiStrokeQ1->StrokeLocation);
				double diff_sizex = (myStrokes.at(iStroke).NeiStrokeQ1->StrokeScale(0) - myStrokes.at(iStroke).StrokeScale(0));
				double diff_sizey = (myStrokes.at(iStroke).NeiStrokeQ1->StrokeScale(1) - myStrokes.at(iStroke).StrokeScale(1));

				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}
			if (myStrokes.at(iStroke).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(iStroke).StrokeLocation - myStrokes.at(iStroke).NeiStrokeQ2->StrokeLocation);
				double diff_sizex = (myStrokes.at(iStroke).NeiStrokeQ2->StrokeScale(0) - myStrokes.at(iStroke).StrokeScale(0));
				double diff_sizey = (myStrokes.at(iStroke).NeiStrokeQ2->StrokeScale(1) - myStrokes.at(iStroke).StrokeScale(1));
				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}
			if (myStrokes.at(iStroke).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(iStroke).StrokeLocation - myStrokes.at(iStroke).NeiStrokeQ3->StrokeLocation);
				double diff_sizex = (myStrokes.at(iStroke).NeiStrokeQ3->StrokeScale(0) - myStrokes.at(iStroke).StrokeScale(0));
				double diff_sizey = (myStrokes.at(iStroke).NeiStrokeQ3->StrokeScale(1) - myStrokes.at(iStroke).StrokeScale(1));
				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}
			if (myStrokes.at(iStroke).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(iStroke).StrokeLocation - myStrokes.at(iStroke).NeiStrokeQ4->StrokeLocation);
				double diff_sizex = (myStrokes.at(iStroke).NeiStrokeQ4->StrokeScale(0) - myStrokes.at(iStroke).StrokeScale(0));
				double diff_sizey = (myStrokes.at(iStroke).NeiStrokeQ4->StrokeScale(1) - myStrokes.at(iStroke).StrokeScale(1));
				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}

			double R_sx = 0;
			double R_sy = 0;
			R_sx = (refStrokes.at(iStroke).StrokeScale(0) - myStrokes.at(iStroke).StrokeScale(0));
			R_sy = (refStrokes.at(iStroke).StrokeScale(1) - myStrokes.at(iStroke).StrokeScale(1));

			double random_num_x = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			double random_num_y = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

			myStrokes.at(iStroke).StrokeScale(0) = (float)(myStrokes.at(iStroke).StrokeScale(0) + R_sx + mSizeContrast * D_sx + RANDOM_RANGE* random_num_x);
			myStrokes.at(iStroke).StrokeScale(1) = (float)(myStrokes.at(iStroke).StrokeScale(1) + R_sy + mSizeContrast * D_sy + RANDOM_RANGE* random_num_y);
		}

	}

	// refine StrokeSize to be in range [minBrushScale, maxBrushScale]
	for (int i = 0; i < myStrokes.size(); i++)
	{
		if (myStrokes.at(i).StrokeScale(0)>Coarseness::maxScale)
		{
			myStrokes.at(i).StrokeScale(0) = Coarseness::maxScale;
		}
		if (myStrokes.at(i).StrokeScale(0) < Coarseness::minScale)
		{
			myStrokes.at(i).StrokeScale(0) = Coarseness::minScale;
		}

		if (myStrokes.at(i).StrokeScale(1)>Coarseness::maxScale)
		{
			myStrokes.at(i).StrokeScale(1) = Coarseness::maxScale;
		}
		if (myStrokes.at(i).StrokeScale(1) < Coarseness::minScale)
		{
			myStrokes.at(i).StrokeScale(1) = Coarseness::minScale;
		}
	}

}


void updateLightness(std::vector<myStroke> & StrokeList, double mLightnessContrast)
{

	std::vector<double>refLightness;
	for (int i = 0; i < StrokeList.size(); i++)
	{
		refLightness.push_back(StrokeList.at(i).ColorLightness);
	}
	for (int n = 0; n < StrokeList.size(); n++){
		for (int i = 0; i < N_ITERATION; i++){

			//step 1 compute D(theta)
			double D_cl = 0;

			if (StrokeList.at(n).NeiStrokeQ1){
				double dist = cv::norm(StrokeList.at(n).StrokeLocation - StrokeList.at(n).NeiStrokeQ1->StrokeLocation);
				double diff_color_l = (StrokeList.at(n).NeiStrokeQ1->ColorLightness - StrokeList.at(n).ColorLightness);

				D_cl += 1 / dist * diff_color_l;

			}
			if (StrokeList.at(n).NeiStrokeQ2){
				double dist = cv::norm(StrokeList.at(n).StrokeLocation - StrokeList.at(n).NeiStrokeQ2->StrokeLocation);
				double diff_color_l = (StrokeList.at(n).NeiStrokeQ2->ColorLightness - StrokeList.at(n).ColorLightness);


				D_cl += 1 / dist * diff_color_l;


			}
			if (StrokeList.at(n).NeiStrokeQ3){
				double dist = cv::norm(StrokeList.at(n).StrokeLocation - StrokeList.at(n).NeiStrokeQ3->StrokeLocation);
				double diff_color_l = (StrokeList.at(n).NeiStrokeQ3->ColorLightness - StrokeList.at(n).ColorLightness);

				D_cl += 1 / dist * diff_color_l;


			}
			if (StrokeList.at(n).NeiStrokeQ4){
				double dist = cv::norm(StrokeList.at(n).StrokeLocation - StrokeList.at(n).NeiStrokeQ4->StrokeLocation);
				double diff_color_l = (StrokeList.at(n).NeiStrokeQ4->ColorLightness - StrokeList.at(n).ColorLightness);

				D_cl += 1 / dist * diff_color_l;

			}

			double R_cl = 0;
			R_cl = (refLightness.at(n) - StrokeList.at(n).ColorLightness);
			double StochasticNoise = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			StrokeList.at(n).ColorLightness = StrokeList.at(n).ColorLightness + R_cl + mLightnessContrast * D_cl + RANDOM_RANGE * StochasticNoise;

		}

	}
}


void updateChroma(std::vector<myStroke> & myStrokes, double mChromaContrast)
{
	std::vector<myStroke> refStrokes = myStrokes;
	for (int n = 0; n < myStrokes.size(); n++){
		for (int i = 0; i < N_ITERATION; i++){

			//step 1 compute D(theta)
			double D_cl = 0;

			if (myStrokes.at(n).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ1->StrokeLocation);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ1->ColorChroma - myStrokes.at(n).ColorChroma);

				D_cl += 1 / dist * diff_color_l;

			}
			if (myStrokes.at(n).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ2->StrokeLocation);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ2->ColorChroma - myStrokes.at(n).ColorChroma);


				D_cl += 1 / dist * diff_color_l;


			}
			if (myStrokes.at(n).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ3->StrokeLocation);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ3->ColorChroma - myStrokes.at(n).ColorChroma);

				D_cl += 1 / dist * diff_color_l;


			}
			if (myStrokes.at(n).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ4->StrokeLocation);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ4->ColorChroma - myStrokes.at(n).ColorChroma);

				D_cl += 1 / dist * diff_color_l;

			}

			double R_cl = 0;

			R_cl = (refStrokes.at(n).ColorChroma - myStrokes.at(n).ColorChroma);
			double StochasticNoise = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			myStrokes.at(n).ColorChroma = myStrokes.at(n).ColorChroma + R_cl + mChromaContrast * D_cl + RANDOM_RANGE * StochasticNoise;

		}

	}
}

void updateHue(std::vector<myStroke> & myStrokes, double mHueContrast)
{
	std::vector<myStroke> refStrokes = myStrokes;
	for (int n = 0; n < myStrokes.size(); n++){
		for (int i = 0; i < N_ITERATION; i++){

			//step 1 compute D(theta)

			double D_ch = 0;
			if (myStrokes.at(n).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ1->StrokeLocation);

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ1->ColorHue - myStrokes.at(n).ColorHue);


				D_ch += 1 / dist * diff_color_h;
			}
			if (myStrokes.at(n).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ2->StrokeLocation);

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ2->ColorHue - myStrokes.at(n).ColorHue);


				D_ch += 1 / dist * diff_color_h;

			}
			if (myStrokes.at(n).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ3->StrokeLocation);

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ3->ColorHue - myStrokes.at(n).ColorHue);


				D_ch += 1 / dist * diff_color_h;

			}
			if (myStrokes.at(n).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(n).StrokeLocation - myStrokes.at(n).NeiStrokeQ4->StrokeLocation);

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ4->ColorHue - myStrokes.at(n).ColorHue);

				D_ch += 1 / dist * diff_color_h;

			}


			double R_ch = 0;

			R_ch = sin(refStrokes.at(n).ColorHue - myStrokes.at(n).ColorHue);


			double random_num_b = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

			myStrokes.at(n).ColorHue = myStrokes.at(n).ColorHue + R_ch + mHueContrast * D_ch + RANDOM_RANGE * random_num_b;


		}

	}

}
