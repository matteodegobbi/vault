#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv)
{

    if (argc < 2)
    {
        std::cout<<"You should provide the path to the image" << std::endl;
        return 1;
    }
    
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    
    if (img.empty())
    {
        std::cout<<"Image not found" << std::endl;
        return 2;
    }

    int n_channels = img.channels();
    std::cout<< "Number of channels: "<< n_channels << std::endl;

    cv::Mat arr_matr[3];
    cv::split(img,arr_matr);
    cv::namedWindow("Example B",cv::WINDOW_NORMAL);
    cv::namedWindow("Example G",cv::WINDOW_NORMAL);
    cv::namedWindow("Example R",cv::WINDOW_NORMAL);
    cv::resizeWindow("Example R",200,200);
    cv::resizeWindow("Example G",200,200);
    cv::resizeWindow("Example B",200,200);
    cv::imshow("Example B", arr_matr[0]);
    cv::imshow("Example G", arr_matr[1]);
    cv::imshow("Example R", arr_matr[2]);
    cv::Mat arr_matr2[3];
    
    /*
    cv::Mat img_B(img.rows,img.cols,CV_8U);
    cv::Mat img_G(img.rows,img.cols,CV_8U);
    cv::Mat img_R(img.rows,img.cols,CV_8U);
    if (n_channels == 3)
    {
        for (size_t i = 0; i < img.rows; i++)
        {
            for (size_t j = 0; j < img.cols; j++)
            {
                img_B.at<cv::Vec3b>(i,j) = img.at<cv::Vec3b>(i,j)[0];
                img_G.at<cv::Vec3b>(i,j) = img.at<cv::Vec3b>(i,j)[1];
                img_R.at<cv::Vec3b>(i,j) = img.at<cv::Vec3b>(i,j)[2];
            }
            
        }
        
    }
    */

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char key = cv::waitKey(0);

    std::cout<< key << std::endl;
    return 0;
}


