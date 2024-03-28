#include "opencv2/core/mat.hpp"
#include "opencv2/core/matx.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct userdata_type {
  cv::Mat *in;
  cv::Mat *out;
  int threshold;
  cv::Vec3b *reference_color;
  bool task6 = false;
};

// FORWARD DECLARATIONS
void segment_shirt(const cv::Mat &in_img, cv::Mat &out_img, cv::Vec3b ref_color,
                   int threshold);
cv::Mat color_stuff(const cv::Mat &in_img, const cv::Mat &mask);
////////////////////////////
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
  const Mat in_img = *u.in;
  Mat out_img = *u.out;
  int threshold = u.threshold;
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
        Vec3b current = in_img.at<Vec3b>(y + i, x + j);
        b_sum += current[0];
        g_sum += current[1];
        r_sum += current[2];
        counter++;
      }
    }
    *ref_color = (Vec3b){(uchar)(b_sum / counter), (uchar)(g_sum / counter),
                         (uchar)(r_sum / counter)};
    cout << *ref_color << endl; // task 3

    segment_shirt(in_img, out_img, *ref_color, threshold);
    if (!u.task6) {
      cv::imshow("segmneted", out_img);
      cv::waitKey(1);
    } else {
      cv::imshow("segmneted", out_img);
      cv::waitKey(1);
      const Vec3b select_color = {92, 37, 201};
      for (int r = 0; r < out_img.rows; r++) {
        for (int c = 0; c < out_img.cols; c++) {
          Vec3b curr_color = out_img.at<Vec3b>(r, c);
          if (curr_color[0] == 0 && curr_color[1] == 0 && curr_color[2] == 0) {
            out_img.at<Vec3b>(r, c) = in_img.at<Vec3b>(r, c);
          } else {
            out_img.at<Vec3b>(r, c) = select_color;
          }
        }
      }
      cv::imshow("selected task6", out_img);
      cv::waitKey(1);
    }
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
      // float distance = cv::norm(curr_color, ref_color);
      if (distance > threshold) {
        out_img.at<Vec3b>(r, c) = {0, 0, 0};
      } else {
        out_img.at<Vec3b>(r, c) = {255, 255, 255};
      }
    }
  }
}
int main() {
  cv::Mat in_img = cv::imread("robocup.jpg");
  cv::Mat mask_img = cv::imread("robocup.jpg");
  cv::resize(in_img, in_img, cv::Size(), 0.6, 0.6);
  cv::resize(mask_img, mask_img, cv::Size(), 0.6, 0.6);
  cv::Mat in_img_hsv;
  cv::cvtColor(in_img, in_img_hsv, cv::COLOR_BGR2HSV);
  cv::Mat mask_img_hsv = mask_img.clone();
  cv::Mat mask_img_task6 = mask_img.clone();

  // NOTE: task 2
  cv::imshow("input", in_img);
  cv::setMouseCallback("input", &pixel_callback, &in_img);

  // NOTE: task 3 and 4
  cv::Vec3b reference_color = {0, 0, 0};
  const int dist_threshold = 100;
  userdata_type userdata = {.in = &in_img,
                            .out = &mask_img,
                            .threshold = dist_threshold,
                            .reference_color = &reference_color,
                            .task6 = false};
  cv::imshow("T-shirt", in_img);
  cv::setMouseCallback("T-shirt", &neighborhood_callback, &userdata);
  // NOTE: task 5
  cv::Vec3b reference_color_hsv = {0, 0, 0};
  const int dist_threshold_hsv = 100;
  userdata_type userdata_hsv = {
      .in = &in_img_hsv,
      .out = &mask_img_hsv,
      .threshold = dist_threshold_hsv,
      .reference_color = &reference_color_hsv,
      .task6 = false}; // reference color gets set by address
  cv::imshow("T-shirt HSV", in_img_hsv);
  cv::setMouseCallback("T-shirt HSV", &neighborhood_callback, &userdata_hsv);
  // NOTE: task 6
  cv::Vec3b reference_color_task6 = {0, 0, 0};
  const int dist_threshold_task6 = 120;
  userdata_type userdata_task6 = {.in = &in_img,
                                  .out = &mask_img_task6,
                                  .threshold = dist_threshold_task6,
                                  .reference_color = &reference_color_task6,
                                  .task6 = true};
  cv::imshow("task6", in_img);
  cv::setMouseCallback("task6", &neighborhood_callback, &userdata_task6);
  cv::waitKey(0);
}
