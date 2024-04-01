#include "opencv2/core/cvdef.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <vector>

int main() {
  // cv::Mat input_img = cv::imread("pic1.png");
  cv::Mat input_img = cv::imread("Astronaut_original.png");
  cv::Mat edges_img;
  cv::Mat lines_img = input_img.clone();
  cv::Canny(input_img, edges_img, 3, 9, 3);
  // cv::cvtColor(edges_img, lines_img, cv::COLOR_GRAY2BGR);
  std::vector<cv::Vec2f> lines;
  cv::HoughLines(edges_img, lines, 1, CV_PI / 180, 150, 0, 0);
  std::cout << "mi" << std::endl;
  cv::imshow("w1", edges_img);
  for (size_t i = 0; i < lines.size(); i++) {
    using namespace cv;
    float rho = lines[i][0], theta = lines[i][1];
    Point pt1, pt2;
    double a = cos(theta), b = sin(theta);
    double x0 = a * rho, y0 = b * rho;
    constexpr int line_len = 100;
    pt1.x = cvRound(x0 + line_len * (-b));
    pt1.y = cvRound(y0 + line_len * (a));
    pt2.x = cvRound(x0 - line_len * (-b));
    pt2.y = cvRound(y0 - line_len * (a));
    line(lines_img, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
  }
  cv::imshow("w2", lines_img);
  cv::waitKey(0);
  return 0;
}
