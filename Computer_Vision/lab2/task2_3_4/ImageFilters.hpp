#pragma once
#include <opencv2/highgui.hpp>
void maxFilter(cv::Mat& img,cv::Mat& out, int kernel_size);
void minFilter(cv::Mat& img,cv::Mat& out, int kernel_size);
void medianFilter(cv::Mat& img,cv::Mat& out, int kernel_size);