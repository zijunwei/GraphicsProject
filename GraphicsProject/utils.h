#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core.hpp>
#define PI         3.14159265358979323846
#define NUMBER_OF_SUPERPIXELS 40


#define STROKE_DISTANCE_THRESHOLD  60       // 3.2 stroke neighborhood graph threshold 
#define RANDOM_RANGE         0.005          //attribute process for stroke orientation: control the range of random number
#define N_ITERATION_ORIENTATION    20     //number of iterations for stroke process 

//#define LAMBDA_SIZE               0.005    //attribute process for stroke size: size contrast
#define N_ITERATION_SIZE          20      //number of iterations for stroke process size 

//#define LAMBDA_COLOR              0.005    //attribute process for stroke size: size contrast
#define N_ITERATION_COLOR          20      //number of iterations for stroke process size 

namespace BarProperties{

	static  int BarMin = 10;
	static  int BarMax = 100;
	static  int BarInit = 50;
}

//Window settings for Brush Views
namespace WindowPropertyDisplayBrush
{

	static int ColOffset = 50;
	static int RowOffset = 50;

};
//Window settings for Image pre-processing views
namespace WindowPropertyDisplayImage
{
	static int ColOffset = 400;
	static int RowOffset = 50;
	static char *CaptionOriginalImage = "Input Image";
	static char *CaptionSaliencyImage = "Saliency Image";
	static char *CaptionSegmentationImage = "Segmentation Image";

};

namespace WindowsPropertyRsltImage{
	static int ColOffset = 800;
	static int RowOffset = 50;
	static char *CaptionStrokePositions = "Stroke Positions";
	static char *CaptionConnectGraph1 = "Stroke Graph 1";
	static char *CaptionConnectGraph2 = "Stroke Graph 2";

	static char *CaptionRstl = "Result";
}



// convert bar values to real values:
double cvtRange(int barVal, double Scale, double Offset);

namespace Density{
	static double Scale = 0.0025;
	static double Offset = 0;
}
namespace Non_uniformity{
	static double Scale = 0.005;
	static double Offset = 0.0;
}


namespace Coarseness{
	static double minSize = 5;
	static double maxScale = 10;
	static double minScale = 1;
	static double Scale = 0.01;
	static double Offset = 0.2;

}

namespace LocalIostropy{

	static double Scale = 0.0001;
	static double Offset = 0;
}

namespace SizeContrast{

	static double Scale = 0.0001;
	static double Offset = 0;
}

namespace HueContrast{

	static double Scale = 0.01;
	static double Offset = 0;
}

namespace ChromaContrast{
	static double Scale = 0.01;
	static double Offset = 0;
}
namespace LightnessContrast{
	static double Scale = 0.01;
	static double Offset = 0;
}

void ShowSingleImage(const char *caption, const cv::Mat inputImage, const int colOffset, const int rowOffset);
////Windows settings for results 



#endif /* defined(UTILS_H) */