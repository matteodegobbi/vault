#include "opencv2/core.hpp"
#include "opencv2/core/hal/interface.h"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <ostream>
int main(int argc, char **argv) {
  cv::Mat img = cv::imread(argv[1]);
  if (img.empty()) {
    std::cout << "Image not found" << std::endl;
    return 2;
  }
  cv::cvtColor(img, img, cv::COLOR_RGB2GRAY);
  cv::Mat out;
  img.convertTo(out, CV_32FC1);
  out = out / 255;
  cv::dft(out, out);
  std::cout << out << std::endl;
  cv::idft(out, out);

  cv::imwrite("out.png", out);
  return 0;
}
