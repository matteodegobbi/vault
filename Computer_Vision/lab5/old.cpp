#include "opencv2/core.hpp"
#include "opencv2/core/base.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/matx.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "opencv2/imgcodecs.hpp"
#include <iostream>

using namespace cv;
using std::cout;
using std::endl;
int main(int argc, char **argv) {
  Mat in = imread(argc > 1 ? argv[1] : "Asphalt-1.png");
  // Mat binary_image;
  // cvtColor(in, binary_image, COLOR_BGR2GRAY);
  Mat markers(in.rows, in.cols, CV_32SC1, Scalar(0));
  // markers.size
  // markers.at<int>(300, 200) = 1;
  // markers.at<int>(100, 100) = 2;
  std::vector<std::vector<Point>> contours;
  std::vector<Vec4i> hierarchy;
  Mat ingray;
  cvtColor(in, ingray, COLOR_BGR2GRAY);
  imshow("ingray", ingray);
  // GaussianBlur(ingray, blurred, Size(3, 3), 1);
  Mat temp;
  distanceTransform(ingray, temp, DIST_L1, 3);
  Mat erode_ker = getStructuringElement(MORPH_RECT, Size(21, 21));
  dilate(temp, temp, erode_ker);
  dilate(temp, temp, erode_ker);
  dilate(temp, temp, erode_ker);
  // normalize(temp, temp, 0, 255, NORM_MINMAX);
  imshow("dist", temp);

  threshold(temp, temp, 100, 255, THRESH_BINARY);
  imshow("temp", temp);
  // Laplacian(ingray, lap, CV_8U);
  // temp = ingray - lap;

  Mat temp8u;
  temp.convertTo(temp8u, CV_8U);
  cout << "a" << endl;
  findContours(temp8u, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

  for (size_t i = 0; i < contours.size(); i++) {
    drawContours(markers, contours, (int)(i), Scalar((int)(i) + 1), FILLED,
                 LINE_AA, hierarchy);
  }
  // cout << "caa" << endl;
  watershed(in, markers);
  // imshow("iin", in);
  Mat out = in.clone();
  for (int i = 0; i < in.rows; i++) {
    for (int j = 0; j < in.cols; j++) {
      if (markers.at<int>(i, j) < 0) {
        markers.at<int>(i, j) = 255;
        out.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
      }
    }
  }
  // markers.convertTo(out, CV_8UC3);
  //  cout << markers << endl;
  imshow("m", out);
  waitKey(0);
  // cout << markers << endl;
  /*threshold(binary_image, binary_image, 0, 255, THRESH_OTSU | THRESH_BINARY);
  Mat dist_transf;
  distanceTransform(binary_image, dist_transf, DIST_L2, 3);
  normalize(dist_transf, dist_transf, 0, 1.0, NORM_MINMAX);
  imshow("bin", binary_image);
  imshow("dist", dist_transf);
  Mat peaks;
  threshold(dist_transf, peaks, 0.4, 1.0, THRESH_BINARY);
  imshow("peaks", peaks);
  Mat peaks8u;
  peaks.convertTo(peaks8u, CV_8U);
  Mat markers = Mat::zeros(peaks8u.size, CV_32SC1);

  circle(markers, Point(5, 5), 3, CV_RGB(255, 0, 0));
  imshow("mark", markers);*/

  return 0;
}
