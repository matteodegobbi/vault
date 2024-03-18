#include "ImageFilters.hpp"
#include <iostream>
void maxFilter(cv::Mat& img,cv::Mat& out, int kernel_size){
    if (kernel_size%2==0)
    {
        std::cout<< "Error kernel must have odd size" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < img.rows; i++)
    {
        for (size_t j = 0; j < img.cols; j++)
        {
            uchar temp_max = img.at<uchar>(i,j);
            if (i-kernel_size/2 < 0 || 
            j-kernel_size/2 < 0 || 
            i+kernel_size/2 >= img.rows || 
            j+kernel_size/2 >=img.cols)
            {
                out.at<uchar>(i,j)=temp_max;
                continue;
            }
            for (int k = -kernel_size/2; k <= kernel_size/2; k++)
            {

                for (int h = -kernel_size/2; h <= kernel_size/2; h++){

                    uchar curr_pix = img.at<uchar>(i+k,j+h);
                    temp_max = curr_pix>temp_max?curr_pix:temp_max;
                }
            }
            out.at<uchar>(i,j)=temp_max;
            
        }
        
    }
    
}
void minFilter(cv::Mat& img,cv::Mat& out, int kernel_size){
    if (kernel_size%2==0)
    {
        std::cout<< "Error kernel must have odd size" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < img.rows; i++)
    {
        for (size_t j = 0; j < img.cols; j++)
        {
            uchar temp_min= img.at<uchar>(i,j);
            if (i-kernel_size/2 < 0 || 
            j-kernel_size/2 < 0 || 
            i+kernel_size/2 >= img.rows || 
            j+kernel_size/2 >=img.cols)
            {
                out.at<uchar>(i,j)=temp_min;
                continue;
            }
            for (int k = -kernel_size/2; k <= kernel_size/2; k++)
            {

                for (int h = -kernel_size/2; h <= kernel_size/2; h++){

                    uchar curr_pix = img.at<uchar>(i+k,j+h);
                    temp_min = curr_pix<temp_min?curr_pix:temp_min;
                }
            }
            out.at<uchar>(i,j)=temp_min;
            
        }
        
    }
    
}

void medianFilter(cv::Mat& img,cv::Mat& out, int kernel_size){
    if (kernel_size%2==0)
    {
        std::cout<< "Error kernel must have odd size" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < img.rows; i++)
    {
        for (size_t j = 0; j < img.cols; j++)
        {
            if (i-kernel_size/2 < 0 || 
            j-kernel_size/2 < 0 || 
            i+kernel_size/2 >= img.rows || 
            j+kernel_size/2 >=img.cols)
            {
                out.at<uchar>(i,j)=img.at<uchar>(i,j);
                continue;
            }
            std::vector<uchar> v;
            
            for (int k = -kernel_size/2; k <= kernel_size/2; k++)
            {
                for (int h = -kernel_size/2; h <= kernel_size/2; h++){

                    uchar curr_pix = img.at<uchar>(i+k,j+h);
                    v.push_back(curr_pix);
                }
            }
            std::nth_element(v.begin(),v.begin()+v.size()/2,v.end());
            out.at<uchar>(i,j)= v[v.size()/2];
        }
        
    }
    
}