// ParamBox.h : header file
//

#pragma once


// 
class ParamBox
{
public:
	double mDensity=0.5;                 // number of strokes in z_strokeSampling function
	double mNon_Uniformity=0.5;          // controls the z_strokeSampling part ... saliency vs number of strokes 
	double mLocal_Iostropy=0.005;
	double mCoarseness=0.1;                // initial size = coarseness * original size(300 by 100 in our case )
	double mSize_Contrast=0.005;
	double mLightness_Contrast=0.005;
	double mChroma_Constrast=0.005;
	double mHue_Constrast=0.005;
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
