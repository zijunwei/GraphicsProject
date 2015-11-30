#ifndef _Z_SALIENCY_H__
#define _Z_SALIENCY_H__
#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/persistence.hpp>
#include "opencv2/imgproc.hpp"

bool computeSaliency(cv::InputArray image,cv:: OutputArray saliencyMap);
void computeGraidentOrientation(cv::Mat inputImage, cv::Mat & outputGradientOrientation, cv::Mat & outputGradientRatio);
#endif

