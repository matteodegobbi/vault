#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ImageFilters.hpp"
int main(int argc, char **argv) {
  std::string imgname;
  if (argc < 2)
    imgname = "Garden.jpg";
  else
    imgname = argv[1];
  std::cout << imgname << std::endl;
  cv::Mat img = cv::imread(imgname);

  if (img.empty()) {
    std::cout << "Image not found" << std::endl;
    return 2;
  }
  cv::Mat gray;
  cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

  cv::Mat out = gray.clone();
  cv::Mat outblur = gray.clone();
  // cv::resize(gray, out, cv::Size(), 0.75, 0.75);
  medianFilter(gray, out, 3);
  cv::GaussianBlur(gray, outblur, cv::Size(3, 9), 10);
  // cv::imshow("window1", out);
  cv::imshow("gaussianblur", outblur);
  // cv::imwrite("task2/outmin.png", out);
  cv::waitKey(0);
  return 0;
}
