#include "opencv2/core/types.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

void draw_hist(const cv::Mat &hist, cv::Mat &histImage, int histSize, int width,
               int height, cv::Scalar color) {
  int bin_width = cvRound((double)width / histSize);
  cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
  for (int i = 1; i < histSize; i++) {
    using namespace cv;
    rectangle(
        histImage,
        Point(bin_width * (i - 1), height - cvRound(hist.at<float>(i - 1))),
        Point(bin_width * (i), height), color, 1);
  }
}
// line(histImage,
//      Point(bin_width * (i - 1), height - cvRound(hist.at<float>(i - 1))),
//      Point(bin_width * (i), height - cvRound(hist.at<float>(i))), color,
//      3);
int main(int argc, char **argv) {
  cv::Mat img = cv::imread("Garden.jpg");

  if (img.empty()) {
    std::cout << "Image not found" << std::endl;
    return 2;
  }
  cv::Mat originalGs;
  cv::Mat hist;
  cv::cvtColor(img, originalGs, cv::COLOR_RGB2GRAY);
  cv::imwrite("Garden_grayscale.png", originalGs);

  constexpr float range[2] = {0, 256};
  const float *histRange[2] = {range};
  constexpr int bins = 256;
  constexpr bool uniform = true, accumulate = false;
  calcHist(&originalGs, 1, 0, cv::Mat(), hist, 1, &bins, histRange, uniform,
           accumulate);
  int hist_w = 1200, hist_h = 800;
  cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(255, 255, 255));

  draw_hist(hist, histImage, bins, hist_w, hist_h, cv::Scalar(100, 0, 0));
  cv::imshow("hist before equalization", histImage);

  cv::Mat equalizedGs;
  cv::equalizeHist(originalGs, equalizedGs);
  histImage = cv::Mat(hist_h, hist_w, CV_8UC3, cv::Scalar(255, 255, 255));
  calcHist(&equalizedGs, 1, 0, cv::Mat(), hist, 1, &bins, histRange, uniform,
           accumulate);
  draw_hist(hist, histImage, bins, hist_w, hist_h, cv::Scalar(0, 0, 200));
  cv::imshow("hist after equalization", histImage);
  cv::imshow("original image", originalGs);

  cv::imshow("equalized image", equalizedGs);
  cv::imwrite("equalized.png", equalizedGs);
  cv::waitKey(0);
  return 0;
}
