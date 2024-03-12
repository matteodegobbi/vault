#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout<<"You should provide the path to the image" << std::endl;
        return 1;
    }
    
    cv::Mat img = cv::imread(argv[1]);
    
    if (img.empty())
    {
        std::cout<<"Image not found" << std::endl;
        return 2;
    }

    int n_channels = img.channels();
    std::cout<< "Number of channels: "<< n_channels << std::endl;

    constexpr int CHANNEL_TO_DELETE {2};
    if (n_channels == 3)
    {
        for (size_t i = 0; i < img.rows; i++)
        {
            for (size_t j = 0; j < img.cols; j++)
            {
                img.at<cv::Vec3b>(i,j)[CHANNEL_TO_DELETE] = 0;
            }
            
        }
        
    }
    
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char key = cv::waitKey(0);

    std::cout<< key << std::endl;
    return 0;
}


