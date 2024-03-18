#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("Garden.jpg");
    
    if (img.empty())
    {
        std::cout<<"Image not found" << std::endl;
        return 2;
    }
    cv::Mat out;
    cv::cvtColor(img,out,cv::COLOR_RGB2GRAY);
    cv::imwrite("task1/Garden_grayscale.png",out);
    return 0;
}


