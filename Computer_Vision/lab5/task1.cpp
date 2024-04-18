#include "opencv2/core.hpp"
#include "opencv2/core/base.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/matx.hpp"
#include "opencv2/core/operations.hpp"
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
  Mat temp;
  Mat labels;
  Mat centers;
  in.convertTo(temp, CV_32F);
  constexpr int n_clusters = 2;
  TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.01);
  kmeans(temp, n_clusters, labels, criteria, 7, KMEANS_PP_CENTERS, centers);

  Mat out;
  Mat superimposed = in.clone();
  temp.convertTo(out, CV_8UC3);
  cvtColor(out, out, COLOR_BGR2GRAY);
  threshold(out, out, 15, 255, THRESH_BINARY);
  Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
  morphologyEx(out, out, MORPH_OPEN, kernel);
  imshow("out", out);

  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      if (out.at<uchar>(i, j) == 0) {
        superimposed.at<Vec3b>(i, j) = Vec3b(100, 0, 255);
      }
    }
  }
  imwrite("asf3.jpg", out);
  imwrite("asf3super.jpg", superimposed);
  imshow("superimposed", superimposed);
  waitKey(0);
  return 0;
}
