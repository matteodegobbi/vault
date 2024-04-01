#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
cv::Mat input_img;
cv::Mat canny_img;
int lowThreshold = 0;
constexpr int max_lowThreshold = 100;
constexpr int ratio = 3;
constexpr int kernel_size = 3;
static void CannyThreshold(int, void *) {
  using namespace cv;
  blur(src_gray, detected_edges, Size(3, 3));
  Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio,
        kernel_size);
  dst = Scalar::all(0);
  src.copyTo(dst, detected_edges);
  imshow("w1", dst);
}

int main() {
  createTrackbar("Min Threshold:", "w1", &lowThreshold, max_lowThreshold,
                 CannyThreshold);
  input_img = cv::imread("Astronaut_original.png");
  cv::Canny(input_img, canny_img, 9, 10);
  namedWindow("w1", cv::WINDOW_AUTOSIZE);
  cv::waitKey(0);
  return 0;
}
