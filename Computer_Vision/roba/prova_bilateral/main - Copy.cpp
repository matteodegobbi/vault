#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>

int main() {
  std::cout << "mi" << std::endl;
  cv::Mat input_img = cv::imread("Astronaut_original.png");
  cv::imshow("w1", input_img);
  cv::waitKey(0);
  return 0;
}
