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
  Mat temp;
  GaussianBlur(in, temp, Size(21, 21), 5);
  imshow("blur", temp);
  cvtColor(temp, temp, COLOR_BGR2GRAY);
  threshold(temp, temp, 0, 255, THRESH_OTSU + THRESH_BINARY);

  imshow("trhrsh", temp);
  waitKey(0);
  return 0;
}
