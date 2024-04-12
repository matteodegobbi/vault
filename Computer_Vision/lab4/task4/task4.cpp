#include "opencv2/core.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

using namespace cv;
using std::cout;

void find_road_sign_hough(const Mat &in, Mat &out) {
  Mat final = in.clone();
  Mat gray_in;
  cvtColor(in, gray_in, COLOR_BGR2GRAY);
  medianBlur(gray_in, gray_in, 3);
  Mat canny_out;
  Laplacian(gray_in, out, CV_8U);
  Mat morph = getStructuringElement(MORPH_RECT, Size(5, 5));
  dilate(out, out, morph);
  imshow("dilated Laplacian", out);
  std::vector<Vec3f> circles;
  HoughCircles(out, circles, HOUGH_GRADIENT, 1, out.rows / 10, 100, 30, 5, 15);
  // cout << circles.size() << std::endl;
  for (size_t i = 0; i < circles.size(); i++) {
    Vec3i c = circles[i];
    Point center = Point(c[0], c[1]);
    circle(final, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
    int radius = c[2];
    circle(final, center, radius, Scalar(100, 0, 255), 3, LINE_AA);
  }

  imshow("detected road sign", final);
  waitKey(0);
}
int main(void) {
  Mat src = imread("street_scene.png");
  Mat dst;
  if (src.empty()) {
    cout << "Error loading src1 \n";
    return -1;
  }
  find_road_sign_hough(src, dst);
  return 0;
}
