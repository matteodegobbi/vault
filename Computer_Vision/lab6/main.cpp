#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <ostream>

using namespace cv;
using std::cout;
using std::endl;
int main(int argc, char **argv) {

  if (argc < 3)
    return -1;
  Mat im1 = imread(argv[1]);
  Mat im2 = imread(argv[2]);

  Ptr<SIFT> detector = SIFT::create();
  std::vector<KeyPoint> keypoints1;
  std::vector<KeyPoint> keypoints2;
  Mat descriptors1, descriptors2;
  detector->detectAndCompute(im1, noArray(), keypoints1, descriptors1);
  detector->detectAndCompute(im2, noArray(), keypoints2, descriptors2);

  Ptr<DescriptorMatcher> matcher =
      DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
  std::vector<std::vector<DMatch>> knn_matches;
  cout << "a" << endl;
  matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
  Mat out;
  float ratio_thresh = 0.5f;
  std::vector<DMatch> good_matches;
  for (uint i = 0; i < knn_matches.size(); i++) {
    if (knn_matches[i][0].distance <
        ratio_thresh * knn_matches[i][1].distance) {
      good_matches.push_back(knn_matches[i][0]);
    }
  }

  drawMatches(im1, keypoints1, im2, keypoints2, good_matches, out);

  if (good_matches.size() > 0.04f * min(keypoints1.size(), keypoints2.size())) {

    cout << "good match" << endl;
  }
  imshow("o", out);
  waitKey(0);
  return 0;
}
