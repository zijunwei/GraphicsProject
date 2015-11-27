#ifndef _Z_STROKESAMPLING_H__
#define _Z_STROKESAMPLING_H__
#include "opencv2/core/utility.hpp"
#include "opencv2/core.hpp"
#include <opencv2/core/persistence.hpp>
#include "opencv2/imgproc.hpp"

std::vector<cv::Point2i> z_strokeSampling(cv::Mat image);

#endif
