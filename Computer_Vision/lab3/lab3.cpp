#include "opencv2/core/matx.hpp"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct userdata_type {
  cv::Mat *in;
  cv::Mat *out;
  int *threshold;
  cv::Vec3b *reference_color;
};

void segment_shirt(const cv::Mat &in_img, cv::Mat &out_img, cv::Vec3b ref_color,
                   int threshold);
void pixel_callback(int event, int x, int y, int flags, void *userdata) {
  using namespace cv;
  using namespace std;
  Mat *img_ptr = static_cast<Mat *>(userdata);
  if (event == EVENT_LBUTTONDOWN) {
    cout << img_ptr->at<Vec3b>(y, x) << endl;
  }
}

void neighborhood_callback(int event, int x, int y, int flags, void *userdata) {
  using namespace cv;
  using namespace std;
  constexpr int kernel_size = 9;
  userdata_type u = *static_cast<userdata_type *>(userdata);
  Mat in_img = *u.in;
  Mat out_img = *u.out;
  int threshold = *u.threshold;
  Vec3b *ref_color = u.reference_color;
  if (true || event == EVENT_LBUTTONDOWN) {
    int counter = 0;
    int b_sum = 0;
    int g_sum = 0;
    int r_sum = 0;
    for (int i = -kernel_size / 2; i <= kernel_size / 2; i++) {
      for (int j = -kernel_size / 2; j <= kernel_size / 2; j++) {
        if (y + i < 0 || x + j < 0 || y + i >= in_img.rows ||
            x + j >= in_img.cols) {
          continue;
        }

        // cout << "hr" << x + j << endl;
        // cout << "vr" << y + i << endl;
        Vec3b current = in_img.at<Vec3b>(y + i, x + j);
        b_sum += current[0];
        g_sum += current[1];
        r_sum += current[2];
        // cout << current << endl;
        // img_ptr->at<Vec3b>(y + i, x + j) = {255, 255, 255};
        counter++;
      }
    }
    cout << "average" << ((float)b_sum) / counter << ','
         << ((float)g_sum) / counter << ',' << ((float)r_sum) / counter << endl;
    *ref_color = (Vec3b){(uchar)(b_sum / counter), (uchar)(g_sum / counter),
                         (uchar)(r_sum / counter)};
    // cv::imshow("input", *img_ptr);
    // cv::waitKey(1);

    // std::cout << reference_color << std::endl;
    segment_shirt(in_img, out_img, *ref_color, threshold);
  }
}

void segment_shirt(const cv::Mat &in_img, cv::Mat &out_img, cv::Vec3b ref_color,
                   int threshold) {
  using namespace cv;
  using namespace std;
  for (int r = 0; r < out_img.rows; r++) {
    for (int c = 0; c < out_img.cols; c++) {
      Vec3b curr_color = in_img.at<Vec3b>(r, c);
      int distance = abs(curr_color[0] - ref_color[0]) +
                     abs(curr_color[1] - ref_color[1]) +
                     abs(curr_color[2] - ref_color[2]);
      if (distance > threshold) {
        out_img.at<Vec3b>(r, c) = {0, 0, 0};
      } else {
        out_img.at<Vec3b>(r, c) = {255, 255, 0};
      }
    }
  }
  cv::imshow("segmneted", out_img);
  cv::waitKey(1);
}
int main() {
  cv::Mat in_img = cv::imread("robocup.jpg");
  cv::cvtColor(in_img, in_img, cv::COLOR_BGR2HSV);
  cv::Vec3b reference_color = {0, 0, 0};
  int dist_threshold = 100;
  cv::Mat out_img = cv::imread("robocup.jpg");
  cv::resize(in_img, in_img, cv::Size(), 0.6, 0.6);
  cv::resize(out_img, out_img, cv::Size(), 0.6, 0.6);
  cv::imshow("input", in_img);
  // cv::imshow("input2", in_img);
  //   cv::setMouseCallback("input", &pixel_callback, &in_img);
  // cv::Vec3b reference_color = {0, 0, 0};
  userdata_type userdata = {
      .in = &in_img,
      .out = &out_img,
      .threshold = &dist_threshold,
      .reference_color =
          &reference_color}; // reference color gets set by address

  cv::setMouseCallback("input", &neighborhood_callback, &userdata);
  std::cout << "asd" << std::endl;
  cv::waitKey(0);
}
