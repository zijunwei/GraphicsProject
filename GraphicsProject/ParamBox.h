// ParamBox.h : header file
//

#pragma once


// 
class ParamBox
{
public:
	double mDensity=0.5;
	double mNon_Uniformity=0.5; 
	double mLocal_Iostropy=0.5;
	double mCoarseness=0.5;
	double mSize_Contrast=0.5;
	double mLightness_Contrast=0.5;
	double mChroma_Constrast=0.5;
	double mHue_Constrast=0.5;
	// Construction
public:
	ParamBox();	// standard constructor
	ParamBox(double Density, double Non_Uniformity, double Local_Iostropy, 
		     double Coarseness, double Size_Contrast, double Lightness_Contrast, 
			 double Chroma_Constrast, double Hue_Constrast):
			 mDensity(Density), mNon_Uniformity(Non_Uniformity), mLocal_Iostropy(Local_Iostropy),
			 mSize_Contrast(Size_Contrast), mLightness_Contrast(Lightness_Contrast), mChroma_Constrast(Chroma_Constrast),
			 mHue_Constrast(Hue_Constrast){};

};
