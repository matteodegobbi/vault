#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout<<"You should provide the path to the image" << std::endl;
        return 1;
    }
    
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    
    if (img.empty())
    {
        std::cout<<"Image not found" << std::endl;
        return 2;
    }

    std::cout<< "Number of channels: "<< img.channels() << std::endl;
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char key = cv::waitKey(0);

    std::cout<< key << std::endl;
    return 0;
}


