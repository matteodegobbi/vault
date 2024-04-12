#include "opencv2/core.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

using namespace cv;
using std::cout;

struct line_params {
  double m;
  double b;
};
constexpr int line_valid_count = 200;
constexpr double distance_valid = 1.0;

// PERF: these constants are used to improve performance
constexpr double ignore_radius = 150;
constexpr int lines_vec_reserve = 202000;
constexpr int coords_vec_reserve = 2000;

void find_road_lines(const Mat &in, Mat &out) {
  Mat gray_in;
  cvtColor(in, gray_in, COLOR_BGR2GRAY);
  Mat threshold_in;
  threshold(gray_in, threshold_in, 250, 255, THRESH_TOZERO);
  // imshow("thresholded in", threshold_in);
  constexpr int morph_size = 7;
  Mat stucturing_el =
      getStructuringElement(MORPH_RECT, Size(morph_size, morph_size));
  Mat morphed;
  erode(threshold_in, morphed, stucturing_el);
  stucturing_el = getStructuringElement(MORPH_RECT, Size(11, 11));
  dilate(morphed, morphed, stucturing_el);
  Mat temp = threshold_in - morphed;
  // imshow("morphed", morphed);
  // imshow("white box removed", temp);
  Mat sobel_out;
  Sobel(temp, sobel_out, CV_8U, 1, 0);
  // imshow("Sobel", sobel_out);
  std::vector<Vec2i> coords;
  coords.reserve(coords_vec_reserve);
  for (int i = 0; i < sobel_out.rows; i++) {
    for (int j = 0; j < sobel_out.cols; j++) {
      if (sobel_out.at<uchar>(i, j) != 0) {
        coords.push_back(Vec2i(i, j));
      }
    }
  }
  // cout << coords.size() << std::endl;
  std::vector<line_params> lines;
  lines.reserve(lines_vec_reserve);
  for (int i = 0; i < coords.size(); i++) {
    Vec2i p1 = coords[i];
    // NOTE: we only check from i+1 becuase we dont want to check the same
    // couple twice
    for (int j = i + 1; j < coords.size(); j++) {
      Vec2i p2 = coords[j];
      if (norm(p1 - p2) > ignore_radius) {
        double m = ((double)(p2[1] - p1[1])) / (p2[0] - p1[0]);
        double b = (double)p2[1] - (double)m * p2[0];
        int count = 0;
        for (Vec2i p3 : coords) {
          assert(sqrtf(1 + m * m) != 0);
          double distance = fabs(p3[1] - m * p3[0] - b) / sqrtf(1 + m * m);
          if (distance < distance_valid) {
            count++;
          }
        }
        if (count > line_valid_count) {
          lines.push_back({.m = m, .b = b});
        }
      }
    }
  }
  out = in.clone();
  // cout << lines.size() << std::endl;
  for (line_params pars : lines) {
    // NOTE: order is y coord, x coord
    Point p = Point(pars.b, 0);
    Point q = Point((pars.m * (in.cols - 1) + pars.b), in.cols - 1);
    line(out, p, q, Scalar(0, 0, 255));
  }
  imshow("final image with lines", out);
  waitKey(0);
}
int main(void) {
  Mat src = imread("street_scene.png");
  Mat dst;
  if (src.empty()) {
    cout << "Error loading src1 \n";
    return -1;
  }
  find_road_lines(src, dst);
  return 0;
}
