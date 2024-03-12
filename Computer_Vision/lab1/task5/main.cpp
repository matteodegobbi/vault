#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv)
{

    cv::Mat v_grad(256,256,CV_8UC1);
    cv::Mat h_grad(256,256,CV_8UC1);
    for (size_t i = 0; i < 256; i++)
    {
        for (size_t j = 0; j < 256; j++)
        {
            v_grad.at<uchar>(i,j)=i;
            h_grad.at<uchar>(i,j)=j;
        }
        
    }
    cv::Mat chess20(300,300,CV_8UC1);
    cv::Mat chess50(300,300,CV_8UC1);
    for (size_t i = 0; i < 300; i++)
    {
        for (size_t j = 0; j < 300; j++)
        {
            if ((j%40 <20 && i%40 < 20)||(j%40 >20 && i%40 > 20))
            {
                chess20.at<uchar>(i,j)=255;
            }else
            {
                chess20.at<uchar>(i,j)=0;
            }
            
            
        }
    }
    
    cv::imshow("vgrad",v_grad);
    cv::imshow("hgrad",h_grad);
    cv::imshow("chess20",chess20);
    char key = cv::waitKey(0);
    
    return 0;
}


