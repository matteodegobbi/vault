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
  cv::Mat outblur = gray.clone();
  // cv::resize(gray, out, cv::Size(), 0.75, 0.75);

  minFilter(gray, out_min, 3);
  maxFilter(gray, out_max, 3);
  auto start = std::chrono::high_resolution_clock::now();
  medianFilter(gray, out_median, 3);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << duration.count() << std::endl;
  cv::imshow("min", out_min);
  cv::imshow("max", out_max);
  cv::imshow("median", out_median);
  // FIX:metti a posto questa roba che serve per la task 3
  // FIX:metti a posto questa roba che serve per la task 3
  // FIX:metti a posto questa roba che serve per la task 3
  // FIX:metti a posto questa roba che serve per la task 3
  // FIX:metti a posto questa roba che serve per la task 3
  // cv::GaussianBlur(gray, outblur, cv::Size(3, 9), 10);
  // cv::imshow("window1", out);
  cv::imshow("gaussianblur", outblur);
  // cv::imwrite("task2/outmin.png", out);
  cv::waitKey(0);
  return 0;
}
