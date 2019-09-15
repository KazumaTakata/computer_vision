#include "opencv2/opencv.hpp"
#include <cmath>

#ifndef NVectorC
#define NVectorC

double CV_Mean(cv::Mat mat);
double CV_Deviation(cv::Mat mat, double mean);
void CV_Whiten(cv::Mat inputmat, cv::Mat outputmat);

#endif