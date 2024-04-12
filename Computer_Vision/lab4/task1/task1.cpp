#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

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
  Canny(data.in, data.out, thres1, thres2);
  imshow("Canny output", data.out);
}
int main(void) {
  Mat src1 = imread("street_scene.png");
  Mat dst;
  if (src1.empty()) {
    cout << "Error loading src1 \n";
    return -1;
  }
  namedWindow("Canny output", WINDOW_AUTOSIZE);
  int threshold1 = 10;
  int threshold2 = 20;
  userdata_t data = {.in = src1,
                     .out = dst,
                     .threshold1 = &threshold1,
                     .threshold2 = &threshold2};
  createTrackbar("threshold 1", "Canny output", &threshold1,
                 canny_max_threshold, on_trackbar, &data);
  createTrackbar("threshold 2", "Canny output", &threshold2,
                 canny_max_threshold, on_trackbar, &data);
  waitKey(0);
  return 0;
}
