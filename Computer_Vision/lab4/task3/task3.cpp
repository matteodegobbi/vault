#include "opencv2/core.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

using namespace cv;
using std::cout;

void find_road_lines_hough(const Mat &in, Mat &out) {
  Mat final = in.clone();
  Mat gray_in;
  cvtColor(in, gray_in, COLOR_BGR2GRAY);
  Mat threshold_in;
  threshold(gray_in, threshold_in, 250, 255, THRESH_TOZERO);
  Mat canny_out;
  Canny(threshold_in, canny_out, 300, 500);
  constexpr int morph_size = 2;
  Mat stucturing_el =
      getStructuringElement(MORPH_RECT, Size(morph_size, morph_size));
  Mat morphed;
  dilate(canny_out, morphed, stucturing_el);
  imshow("after dilation", morphed);
  imshow("canny output", canny_out);
  out = morphed.clone();
  std::vector<Vec2f> lines;
  HoughLines(out, lines, 1, CV_PI / 180, 150);
  // draw lines as in opencv docs
  for (int i = 0; i < lines.size(); i++) {
    float rho = lines[i][0], theta = lines[i][1];
    Point pt1, pt2;
    double m = cos(theta), b = sin(theta);
    double x0 = m * rho, y0 = b * rho;
    pt1.x = cvRound(x0 + 1000 * (-b));
    pt1.y = cvRound(y0 + 1000 * (m));
    pt2.x = cvRound(x0 - 1000 * (-b));
    pt2.y = cvRound(y0 - 1000 * (m));
    line(final, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
  }

  imshow("detected lines", final);
  waitKey(0);
}
int main(void) {
  Mat src = imread("street_scene.png");
  Mat dst;
  if (src.empty()) {
    cout << "Error loading src1 \n";
    return -1;
  }
  find_road_lines_hough(src, dst);
  return 0;
}
