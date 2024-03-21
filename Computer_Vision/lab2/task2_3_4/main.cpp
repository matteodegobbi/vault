#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "ImageFilters.hpp"
int main(int argc, char **argv) {
  std::string imgname;
  if (argc < 2)
    imgname = "Garden.jpg";
  else
    imgname = argv[1];
  std::cout << imgname << std::endl;
  cv::Mat img = cv::imread(imgname);

  if (img.empty()) {
    std::cout << "Image not found" << std::endl;
    return 2;
  }
  cv::Mat gray;
  cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

  cv::Mat out_min = gray.clone();
  cv::Mat out_max = gray.clone();
  cv::Mat out_median = gray.clone();
  cv::Mat out_blur = gray.clone();
  // cv::resize(gray, out, cv::Size(), 0.75, 0.75);

  int kernel_size = 5;
  minFilter(gray, out_min, kernel_size);
  maxFilter(gray, out_max, kernel_size);
  auto start = std::chrono::high_resolution_clock::now();
  medianFilter(gray, out_median, kernel_size);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << duration.count() << std::endl;
  cv::imshow("min", out_min);
  cv::imshow("max", out_max);
  cv::imshow("median", out_median);

  cv::GaussianBlur(gray, out_blur, cv::Size(1, 9), 7);
  cv::imshow("gaussianblur", out_blur);
  // cv::imshow("window1", out);
  // cv::imwrite("task2/outmin.png", out);
  cv::imwrite("outmin.png", out_min);
  cv::imwrite("outmax.png", out_max);
  cv::imwrite("outmedian.png", out_median);
  cv::imwrite("outblur.png", out_blur);
  cv::waitKey(0);
  return 0;
}
