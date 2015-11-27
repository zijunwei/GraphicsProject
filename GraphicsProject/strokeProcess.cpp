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

			double difx = StrokeList.at(j).stroke_location.x - curStroke->stroke_location.x;
			double dify = StrokeList.at(j).stroke_location.y - curStroke->stroke_location.y;
			//double dist = sqrt(pow(difx, 2) + pow(dify, 2));
			//// now decide which Quadrant current method within

			//double x = 1;
			//double y = curStroke->stroke_grad_orientation;
			//double projLength = sqrt(pow(x, 2) + pow(y, 2));
			double rectified_dif_x = (difx * cos(curStroke->stroke_grad_orientation) + dify*sin(curStroke->stroke_grad_orientation));
			double rectified_dif_y = (difx*(-sin(curStroke->stroke_grad_orientation)) + dify*cos(curStroke->stroke_grad_orientation));
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

		if (curStroke->NeiStrokeQ1 && (segMask.at<int>(curStroke->stroke_location.y, curStroke->stroke_location.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ1->stroke_location.y, curStroke->NeiStrokeQ1->stroke_location.x)
			|| cv::norm(curStroke->stroke_location - curStroke->NeiStrokeQ1->stroke_location) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ1 = NULL;
		}
		if (curStroke->NeiStrokeQ2 && (segMask.at<int>(curStroke->stroke_location.y, curStroke->stroke_location.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ2->stroke_location.y, curStroke->NeiStrokeQ2->stroke_location.x)
			|| cv::norm(curStroke->stroke_location - curStroke->NeiStrokeQ2->stroke_location) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ2 = NULL;
		}
		if (curStroke->NeiStrokeQ3 && (segMask.at<int>(curStroke->stroke_location.y, curStroke->stroke_location.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ3->stroke_location.y, curStroke->NeiStrokeQ3->stroke_location.x)
			|| cv::norm(curStroke->stroke_location - curStroke->NeiStrokeQ3->stroke_location) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ3 = NULL;
		}
		if (curStroke->NeiStrokeQ4 && (segMask.at<int>(curStroke->stroke_location.y, curStroke->stroke_location.x) !=
			segMask.at<int>(curStroke->NeiStrokeQ4->stroke_location.y, curStroke->NeiStrokeQ4->stroke_location.x)
			|| cv::norm(curStroke->stroke_location - curStroke->NeiStrokeQ4->stroke_location) > STROKE_DISTANCE_THRESHOLD))
		{
			curStroke->NeiStrokeQ4 = NULL;
		}
	}
} //end of connectStrokeGraph




void initStrokeSize(std::vector<myStroke> & StrokeList, cv::Mat saliencyImage)
{
	double minSaliency = INFINITY;
	//first of all decide the minimal size would be (10,30);
	for (int i = 0; i < StrokeList.size(); i++)
	{
		double unitSaliency = saliencyImage.at<double>(StrokeList.at(i).stroke_location.y, StrokeList.at(i).stroke_location.x);
		if (exp(unitSaliency) < minSaliency)
		{
			minSaliency = exp(unitSaliency);
		}
	}

	for (int i = 0; i < StrokeList.size(); i++)
	{
		StrokeList.at(i).strokeSize = cv::Vec2d(10, 30);
		double unitSaliency = saliencyImage.at<double>(StrokeList.at(i).stroke_location.y, StrokeList.at(i).stroke_location.x);
		StrokeList.at(i).strokeSize = StrokeList.at(i).strokeSize*  minSaliency / exp(unitSaliency);

	}
}

void initStrokeColor(std::vector <myStroke> & StrokeList, cv::Mat refImg){
	for (int i = 0; i < StrokeList.size(); i++)
	{
		//StrokeList.at(i).rgbColor = refImg.at<cv::Vec3b>(StrokeList.at(i).stroke_location.y, StrokeList.at(i).stroke_location.x);
		cv::Vec3d tmpBGR = refImg.at<cv::Vec3b>(StrokeList.at(i).stroke_location.y, StrokeList.at(i).stroke_location.x);
		tmpBGR = tmpBGR / 255.0;
		double L, C, H;
		Rgb2Lch(&L, &C, &H, tmpBGR(2), tmpBGR(1), tmpBGR(0));
		StrokeList.at(i).lchColor = cv::Vec3d(L, C, H / 180 * PI);


	}

}

void initStrokeOrientation(std::vector<myStroke>& StrokeList, cv::Mat salImg)
{//todo this is used to move everything about initializing point locations here

}




void updateOrientation(std::vector<myStroke> & myStrokes){
	//double LAMBDA_THETA = 0.005;
	//TODO: add permutations to the current list of numbers
	std::vector<myStroke>refStrokes = myStrokes;

	for (int n = 0; n < myStrokes.size(); n++){
		for (int i = 0; i < N_ITERATION_ORIENTATION; i++){

			//step 1 compute D(theta)
			double D_theta = 0;
			if (myStrokes.at(n).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ1->stroke_location);
				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ1->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
				D_theta += 1 / dist * diff_angle;
			}
			if (myStrokes.at(n).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ2->stroke_location);
				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ2->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
				D_theta += 1 / dist * diff_angle;
			}
			if (myStrokes.at(n).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ3->stroke_location);
				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ3->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
				D_theta += 1 / dist * diff_angle;
			}
			if (myStrokes.at(n).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ4->stroke_location);
				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ4->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
				D_theta += 1 / dist * diff_angle;
			}

			double R_theta = sin(refStrokes.at(n).stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);

			double random_num = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

			myStrokes.at(n).stroke_grad_orientation = myStrokes.at(n).stroke_grad_orientation + R_theta + LAMBDA_THETA * D_theta + THETA_RANDOM_RANGE* random_num;
		}
	}




}

void updateSize(std::vector<myStroke> & myStrokes)
{
	std::vector<myStroke>  refStrokes = myStrokes;
	for (int n = 0; n < myStrokes.size(); n++){
		for (int i = 0; i < N_ITERATION_SIZE; i++){

			//step 1 compute D(theta)
			double D_sx = 0;
			double D_sy = 0;
			if (myStrokes.at(n).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ1->stroke_location);
				double diff_sizex = (myStrokes.at(n).NeiStrokeQ1->strokeSize(0) - myStrokes.at(n).strokeSize(0));
				double diff_sizey = (myStrokes.at(n).NeiStrokeQ1->strokeSize(1) - myStrokes.at(n).strokeSize(1));

				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}
			if (myStrokes.at(n).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ2->stroke_location);
				double diff_sizex = (myStrokes.at(n).NeiStrokeQ2->strokeSize(0) - myStrokes.at(n).strokeSize(0));
				double diff_sizey = (myStrokes.at(n).NeiStrokeQ2->strokeSize(1) - myStrokes.at(n).strokeSize(1));
				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}
			if (myStrokes.at(n).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ3->stroke_location);
				double diff_sizex = (myStrokes.at(n).NeiStrokeQ3->strokeSize(0) - myStrokes.at(n).strokeSize(0));
				double diff_sizey = (myStrokes.at(n).NeiStrokeQ3->strokeSize(1) - myStrokes.at(n).strokeSize(1));
				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}
			if (myStrokes.at(n).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ4->stroke_location);
				double diff_sizex = (myStrokes.at(n).NeiStrokeQ4->strokeSize(0) - myStrokes.at(n).strokeSize(0));
				double diff_sizey = (myStrokes.at(n).NeiStrokeQ4->strokeSize(1) - myStrokes.at(n).strokeSize(1));
				D_sx += 1 / dist * diff_sizex;
				D_sy += 1 / dist * diff_sizey;
			}

			double R_sx = 0;
			double R_sy = 0;
			R_sx = (refStrokes.at(n).strokeSize(0) - myStrokes.at(n).strokeSize(0));
			R_sy = (refStrokes.at(n).strokeSize(1) - myStrokes.at(n).strokeSize(1));

			double random_num_x = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			double random_num_y = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

			myStrokes.at(n).strokeSize(0) = myStrokes.at(n).strokeSize(0) + R_sx + LAMBDA_SIZE * D_sx + SIZE_RANDOM_RANGE* random_num_x;
			myStrokes.at(n).strokeSize(1) = myStrokes.at(n).strokeSize(1) + R_sy + LAMBDA_SIZE * D_sy + SIZE_RANDOM_RANGE* random_num_y;


		}

	}

}

void updateColor(std::vector<myStroke> & myStrokes){

	std::vector<myStroke> refStrokes = myStrokes;
	for (int n = 0; n < myStrokes.size(); n++){
		for (int i = 0; i < N_ITERATION_COLOR; i++){

			//step 1 compute D(theta)
			double D_cl = 0;
			double D_cc = 0;
			double D_ch = 0;
			if (myStrokes.at(n).NeiStrokeQ1){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ1->stroke_location);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ1->lchColor(0) - myStrokes.at(n).lchColor(0));
				double diff_color_c = (myStrokes.at(n).NeiStrokeQ1->lchColor(1) - myStrokes.at(n).lchColor(1));

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ1->lchColor(2) - myStrokes.at(n).lchColor(2));

				D_cl += 1 / dist * diff_color_l;
				D_cc += 1 / dist * diff_color_c;
				D_ch += 1 / dist * diff_color_h;
			}
			if (myStrokes.at(n).NeiStrokeQ2){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ2->stroke_location);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ2->lchColor(0) - myStrokes.at(n).lchColor(0));
				double diff_color_c = (myStrokes.at(n).NeiStrokeQ2->lchColor(1) - myStrokes.at(n).lchColor(1));

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ2->lchColor(2) - myStrokes.at(n).lchColor(2));

				D_cl += 1 / dist * diff_color_l;
				D_cc += 1 / dist * diff_color_c;
				D_ch += 1 / dist * diff_color_h;

			}
			if (myStrokes.at(n).NeiStrokeQ3){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ3->stroke_location);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ3->lchColor(0) - myStrokes.at(n).lchColor(0));
				double diff_color_c = (myStrokes.at(n).NeiStrokeQ3->lchColor(1) - myStrokes.at(n).lchColor(1));

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ3->lchColor(2) - myStrokes.at(n).lchColor(2));

				D_cl += 1 / dist * diff_color_l;
				D_cc += 1 / dist * diff_color_c;
				D_ch += 1 / dist * diff_color_h;

			}
			if (myStrokes.at(n).NeiStrokeQ4){
				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ4->stroke_location);
				double diff_color_l = (myStrokes.at(n).NeiStrokeQ4->lchColor(0) - myStrokes.at(n).lchColor(0));
				double diff_color_c = (myStrokes.at(n).NeiStrokeQ4->lchColor(1) - myStrokes.at(n).lchColor(1));

				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ4->lchColor(2) - myStrokes.at(n).lchColor(2));

				D_cl += 1 / dist * diff_color_l;
				D_cc += 1 / dist * diff_color_c;
				D_ch += 1 / dist * diff_color_h;

			}

			double R_cl = 0;
			double R_cc = 0;
			double R_ch = 0;
			R_cl = (refStrokes.at(n).lchColor(0) - myStrokes.at(n).lchColor(0));
			R_cc = (refStrokes.at(n).lchColor(1) - myStrokes.at(n).lchColor(1));
			R_ch = sin(refStrokes.at(n).lchColor(2) - myStrokes.at(n).lchColor(2));

			double random_num_r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			double random_num_g = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
			double random_num_b = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

			myStrokes.at(n).lchColor(0) = myStrokes.at(n).lchColor(0) + R_cl + LAMBDA_COLOR * D_cl + COLOR_RANDOM_RANGE * random_num_r;
			myStrokes.at(n).lchColor(1) = myStrokes.at(n).lchColor(1) + R_cc + LAMBDA_COLOR * D_cc + COLOR_RANDOM_RANGE * random_num_g;
			myStrokes.at(n).lchColor(2) = myStrokes.at(n).lchColor(2) + R_ch + LAMBDA_COLOR * D_ch + COLOR_RANDOM_RANGE * random_num_b;


		}

	}

}
