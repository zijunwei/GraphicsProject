#include "stdafx.h"
#include "ReactionDiffusion.h"


//void updateOrientation(std::vector<myStroke> & myStrokes,  int nIter){
//	double LAMBDA_THETA = 0.005;
//	//TODO: add permutations to the current list of numbers
//	std::vector<myStroke>refStrokes = myStrokes;
//	for (int i = 0; i < nIter; i++){
//
//		for (int n = 0; n < myStrokes.size(); n++){
//
//			//step 1 compute D(theta)
//			double D_theta = 0;
//			if (myStrokes.at(n).NeiStrokeQ1){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ1->stroke_location);
//				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ1->stroke_grad_orientation-myStrokes.at(n).stroke_grad_orientation );
//				D_theta += 1 / dist * diff_angle;
//			}
//			if (myStrokes.at(n).NeiStrokeQ2){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ2->stroke_location);
//				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ2->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
//				D_theta += 1 / dist * diff_angle;
//			}
//			if (myStrokes.at(n).NeiStrokeQ3){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ3->stroke_location);
//				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ3->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
//				D_theta += 1 / dist * diff_angle;
//			}
//			if (myStrokes.at(n).NeiStrokeQ4){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ4->stroke_location);
//				double diff_angle = sin(myStrokes.at(n).NeiStrokeQ4->stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
//				D_theta += 1 / dist * diff_angle;
//			}
//
//			double R_theta = sin(refStrokes.at(n).stroke_grad_orientation - myStrokes.at(n).stroke_grad_orientation);
//
//			double random_num =  static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//			myStrokes.at(n).stroke_grad_orientation =myStrokes.at(n).stroke_grad_orientation+  R_theta + LAMBDA_THETA * D_theta + random_num;
//				 
//		}
//	
//	}
//
//
//}

//void updateSize(std::vector<myStroke> & myStrokes, int nIter)
//{
//	double lambda_s = 0.005;
//	std::vector<myStroke>  refStrokes = myStrokes;
//	for (int i = 0; i < nIter; i++){
//		for (int n = 0; n < myStrokes.size(); n++){
//
//			//step 1 compute D(theta)
//			double D_sx = 0;
//			double D_sy = 0;
//			if (myStrokes.at(n).NeiStrokeQ1){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ1->stroke_location);
//				double diff_sizex = (myStrokes.at(n).NeiStrokeQ1->strokeSize(0)- myStrokes.at(n).strokeSize(0));
//				double diff_sizey = (myStrokes.at(n).NeiStrokeQ1->strokeSize(1) - myStrokes.at(n).strokeSize(1));
//
//				D_sx += 1 / dist * diff_sizex;
//				D_sy += 1 / dist * diff_sizey;
//			}
//			if (myStrokes.at(n).NeiStrokeQ2){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ2->stroke_location);
//				double diff_sizex = (myStrokes.at(n).NeiStrokeQ2->strokeSize(0) - myStrokes.at(n).strokeSize(0));
//				double diff_sizey = (myStrokes.at(n).NeiStrokeQ2->strokeSize(1) - myStrokes.at(n).strokeSize(1));
//				D_sx += 1 / dist * diff_sizex;
//				D_sy += 1 / dist * diff_sizey;
//			}
//			if (myStrokes.at(n).NeiStrokeQ3){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ3->stroke_location);
//				double diff_sizex = (myStrokes.at(n).NeiStrokeQ3->strokeSize(0) - myStrokes.at(n).strokeSize(0));
//				double diff_sizey = (myStrokes.at(n).NeiStrokeQ3->strokeSize(1) - myStrokes.at(n).strokeSize(1));
//				D_sx += 1 / dist * diff_sizex;
//				D_sy += 1 / dist * diff_sizey;
//			}
//			if (myStrokes.at(n).NeiStrokeQ4){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ4->stroke_location);
//				double diff_sizex = (myStrokes.at(n).NeiStrokeQ4->strokeSize(0) - myStrokes.at(n).strokeSize(0));
//				double diff_sizey = (myStrokes.at(n).NeiStrokeQ4->strokeSize(1) - myStrokes.at(n).strokeSize(1));
//				D_sx += 1 / dist * diff_sizex;
//				D_sy += 1 / dist * diff_sizey;
//			}
//
//			double R_sx = 0;
//			double R_sy = 0;
//			R_sx = (refStrokes.at(n).strokeSize(0) - myStrokes.at(n).strokeSize(0));
//			R_sy = (refStrokes.at(n).strokeSize(1) - myStrokes.at(n).strokeSize(1));
//
//			double random_num_x = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//			double random_num_y = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//
//			myStrokes.at(n).strokeSize(0) = R_sx + lambda_s * D_sx + random_num_x;
//			myStrokes.at(n).strokeSize(1) = R_sy + lambda_s * D_sy + random_num_y;
//
//
//		}
//
//	}
//
//}
//first convert to lab color space
//void updateColor(std::vector<myStroke> & myStrokes, int nIter){
//
//	double lambda_s = 0.005;
//	std::vector<myStroke> refStrokes = myStrokes;
//	for (int i = 0; i < nIter; i++){
//		for (int n = 0; n < myStrokes.size(); n++){
//
//			//step 1 compute D(theta)
//			double D_cl = 0;
//			double D_cc = 0;
//			double D_ch = 0;
//			if (myStrokes.at(n).NeiStrokeQ1){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ1->stroke_location);
//				double diff_color_l = (myStrokes.at(n).NeiStrokeQ1->lchColor(0) - myStrokes.at(n).lchColor(0));
//				double diff_color_c = (myStrokes.at(n).NeiStrokeQ1->lchColor(1) - myStrokes.at(n).lchColor(1));
//
//				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ1->lchColor(2) - myStrokes.at(n).lchColor(2));
//
//				D_cl += 1 / dist * diff_color_l;
//				D_cc += 1 / dist * diff_color_c;
//				D_ch += 1 / dist * diff_color_h;
//			}
//			if (myStrokes.at(n).NeiStrokeQ2){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ2->stroke_location);
//				double diff_color_l = (myStrokes.at(n).NeiStrokeQ2->lchColor(0) - myStrokes.at(n).lchColor(0));
//				double diff_color_c = (myStrokes.at(n).NeiStrokeQ2->lchColor(1) - myStrokes.at(n).lchColor(1));
//
//				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ2->lchColor(2) - myStrokes.at(n).lchColor(2));
//
//				D_cl += 1 / dist * diff_color_l;
//				D_cc += 1 / dist * diff_color_c;
//				D_ch += 1 / dist * diff_color_h;
//
//			}
//			if (myStrokes.at(n).NeiStrokeQ3){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ3->stroke_location);
//				double diff_color_l = (myStrokes.at(n).NeiStrokeQ3->lchColor(0) - myStrokes.at(n).lchColor(0));
//				double diff_color_c = (myStrokes.at(n).NeiStrokeQ3->lchColor(1) - myStrokes.at(n).lchColor(1));
//
//				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ3->lchColor(2) - myStrokes.at(n).lchColor(2));
//
//				D_cl += 1 / dist * diff_color_l;
//				D_cc += 1 / dist * diff_color_c;
//				D_ch += 1 / dist * diff_color_h;
//
//			}
//			if (myStrokes.at(n).NeiStrokeQ4){
//				double dist = cv::norm(myStrokes.at(n).stroke_location - myStrokes.at(n).NeiStrokeQ4->stroke_location);
//				double diff_color_l = (myStrokes.at(n).NeiStrokeQ4->lchColor(0) - myStrokes.at(n).lchColor(0));
//				double diff_color_c = (myStrokes.at(n).NeiStrokeQ4->lchColor(1) - myStrokes.at(n).lchColor(1));
//
//				double diff_color_h = sin(myStrokes.at(n).NeiStrokeQ4->lchColor(2) - myStrokes.at(n).lchColor(2));
//
//				D_cl += 1 / dist * diff_color_l;
//				D_cc += 1 / dist * diff_color_c;
//				D_ch += 1 / dist * diff_color_h;
//
//			}
//
//			double R_cr = 0;
//			double R_cg = 0;
//			double R_cb = 0;
//			R_cr = (refStrokes.at(n).lchColor(0) - myStrokes.at(n).lchColor(0));
//			R_cg = (refStrokes.at(n).lchColor(1) - myStrokes.at(n).lchColor(1));
//			R_cb = sin(refStrokes.at(n).lchColor(2) - myStrokes.at(n).lchColor(2));
//
//			double random_num_r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//			double random_num_g = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//			double random_num_b = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
//
//			myStrokes.at(n).lchColor(0) = (uchar)R_cr + lambda_s * D_cl + random_num_r;
//			myStrokes.at(n).lchColor(1) = R_cg + lambda_s * D_cc + random_num_g;
//			myStrokes.at(n).lchColor(2) = R_cb + lambda_s * D_ch + random_num_b;
//
//
//		}
//
//	}
//
//}
