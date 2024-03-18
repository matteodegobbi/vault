#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageFilters.hpp"

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(argv[1]);
    
    if (img.empty())
    {
        std::cout<<"Image not found" << std::endl;
        return 2;
    }
    cv::Mat gray;
    cv::cvtColor(img,gray,cv::COLOR_RGB2GRAY);

    cv::Mat out = gray.clone();
    cv::Mat outblur;// = gray.clone();
    medianFilter(gray,out,7);
    cv::GaussianBlur(gray,outblur,cv::Size(3,3),1);
    cv::imshow("window1",out);
    cv::imshow("gaussianblur",outblur);
    cv::imwrite("task2/outmin.png",out);
    cv::waitKey(0);
    return 0;
}


