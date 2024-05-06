#include "opencv2/calib3d.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>

using namespace cv;
using std::cout;
using std::endl;
constexpr double rotation_threshold = 150.0;
constexpr double percent_of_matches_threshold = 0.02;

int main(int argc, char **argv) {

  if (argc < 3)
    return -1;
  Mat im1 = imread(argv[1]);
  Mat im2 = imread(argv[2]);

  Mat descriptors1, descriptors2;

  Ptr<SIFT> detector = SIFT::create();
  std::vector<KeyPoint> keypoints1;
  std::vector<KeyPoint> keypoints2;
  detector->detectAndCompute(im1, noArray(), keypoints1, descriptors1);
  detector->detectAndCompute(im2, noArray(), keypoints2, descriptors2);
  Ptr<DescriptorMatcher> matcher =
      DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
  std::vector<std::vector<DMatch>> knn_matches;
  matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
  Mat out;
  float ratio_thresh = 0.7f;
  std::vector<DMatch> good_matches;
  for (uint i = 0; i < knn_matches.size(); i++) {
    if (knn_matches[i][0].distance <
        ratio_thresh * knn_matches[i][1].distance) {
      good_matches.push_back(knn_matches[i][0]);
    }
  }

  drawMatches(im1, keypoints1, im2, keypoints2, good_matches, out);

  if (good_matches.size() > percent_of_matches_threshold *
                                min(keypoints1.size(), keypoints2.size())) {
    std::vector<Point2f> good_keypoints1;
    std::vector<Point2f> good_keypoints2;
    for (size_t i = 0; i < good_matches.size(); i++) {
      good_keypoints1.push_back(keypoints1[good_matches[i].queryIdx].pt);
      good_keypoints2.push_back(keypoints2[good_matches[i].trainIdx].pt);
    }
    Mat H = findHomography(good_keypoints1, good_keypoints2, RANSAC);
    Mat identity = Mat::eye(H.rows, H.cols, H.type());
    Mat diff_from_identity = (H - identity);
    diff_from_identity = diff_from_identity.mul(diff_from_identity);
    double distance_from_identity = sqrt(sum(diff_from_identity)[0]);
    if (distance_from_identity < rotation_threshold) {
      cout << "good match with no rotation, distance from identity matrix is"
           << distance_from_identity << endl;
    } else {
      cout << "good match with strong trasformation, distance from identity "
              "matrix is"
           << distance_from_identity << endl;
    }

  } else {
    cout << "bad match" << endl;
  }
  imshow("Matches", out);
  std::string file("outimages/");
  file.append(argv[1]);
  file.append(argv[2]);
  file.append(".jpg");
  imwrite(file, out);
  waitKey(0);
  return 0;
}
