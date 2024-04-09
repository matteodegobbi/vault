#include "opencv2/core/hal/interface.h"
#include "opencv2/core/matx.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

using namespace cv;
using std::cout;

struct userdata_t {
  Mat &in;
  Mat &out;
  int *threshold1;
  int *threshold2;
};
constexpr int canny_max_threshold = 500;
static void on_trackbar(int _, void *userdata) {
  userdata_t data = *static_cast<userdata_t *>(userdata);
  double thres1 = (double)*data.threshold1;
  double thres2 = (double)*data.threshold2;
  Mat temp1;
  Mat temp2;

  Mat in_gray;
  in_gray = data.in.clone();
  // cvtColor(data.in, in_gray, COLOR_BGR2GRAY);
  int dilation_size = 8;
  Mat element = getStructuringElement(
      MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1),
      Point(dilation_size, dilation_size));
  // dilate(in_gray, temp1, element);
  erode(in_gray, temp1, element);
  dilate(temp1, temp1, element);
  temp1 = in_gray - temp1;
  imshow("sottrazione", temp1);
  for (int i = 0; i < temp1.rows; i++) {
    for (int j = 0; j < temp1.cols; j++) {
      if (norm(temp1.at<Vec3b>(i, j)) < 250) {
        temp1.at<Vec3b>(i, j) = 0;
      }
    }
  }
  imshow("azzero", temp1);
  Canny(temp1, temp2, thres1, thres2);
  imshow("Canny output", temp2);
  std::vector<std::vector<Point>> contours;
  std::vector<Vec4i> hierarchy;
  findContours(temp2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
  Mat drawing = Mat::zeros(temp2.size(), CV_8UC3);
  RNG rng(12445);
  for (size_t i = 0; i < contours.size(); i++) {
    Scalar color =
        Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
    drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
  }
  imshow("Contours", drawing);
  /*
  for (int i = 0; i < temp1.rows; i++) {
    for (int j = 0; j < temp1.cols; j++) {
      if (norm(data.in.at<Vec3b>(i, j) - Vec3b(255, 255, 255)) > 1000) {
        temp1.at<Vec3b>(i, j) = 0;
      }
    }
  }
salta:;
  GaussianBlur(temp1, temp1, Size(3, 3), 1);
  Canny(temp1, temp2, thres1, thres2);
  //  data.out = in_gray.clone();
  /*
   */
  // imshow("Canny output", temp2);
}
int main(void) {
  Mat src1 = imread("street_scene.png");
  Mat dst;
  if (src1.empty()) {
    cout << "Error loading src1 \n";
    return -1;
  }
  namedWindow("Canny output", WINDOW_AUTOSIZE); // Create Window
  char TrackbarName[50];
  snprintf(TrackbarName, sizeof(TrackbarName), "Alpha x %d",
           canny_max_threshold);
  int threshold1 = 490;
  int threshold2 = 500;
  userdata_t data = {.in = src1,
                     .out = dst,
                     .threshold1 = &threshold1,
                     .threshold2 = &threshold2};
  createTrackbar("track1", "Canny output", &threshold1, canny_max_threshold,
                 on_trackbar, &data);
  createTrackbar("track2", "Canny output", &threshold2, canny_max_threshold,
                 on_trackbar, &data);
  // on_trackbar(threshold1, &data);
  waitKey(0);
  return 0;
}
