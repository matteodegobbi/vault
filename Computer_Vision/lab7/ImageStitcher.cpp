#include "ImageStitcher.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "panoramic_utils.h"
#include <cstdio>
#include <iostream>
#include <opencv2/core/utils/filesystem.hpp>
#include <ostream>
using namespace cv;
ImageStitcher::ImageStitcher(std::string directory, std::string file_extension,
                             double angle) {
  std::vector<std::string> filenames;
  utils::fs::glob(directory, file_extension, filenames);
  if (filenames.size() == 0) {
    std::cout << "No files found with the " << file_extension
              << " file extension in " << directory << " directory"
              << std::endl;
    return;
  }
  imgs.reserve(filenames.size());
  for (int i = 0; i < filenames.size(); ++i) {
    Mat im = imread(filenames[i]);
    Mat cyl = cylindricalProj(im, angle);
    // equalizeHist(cyl, cyl);
    imgs.push_back(cyl);
  }
}

ImageStitcher::~ImageStitcher() {}

int ImageStitcher::stitch_two_images(const Mat &im1, const Mat &im2,
                                     Mat &stitched, int col_offset) {
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
  float ratio_thresh = 0.7f;
  std::vector<DMatch> good_matches;
  for (uint i = 0; i < knn_matches.size(); i++) {
    if (knn_matches[i][0].distance <
        ratio_thresh * knn_matches[i][1].distance) {
      good_matches.push_back(knn_matches[i][0]);
    }
  }

  if (good_matches.size() > percent_of_matches_threshold *
                                min(keypoints1.size(), keypoints2.size())) {
    std::vector<Point2f> good_keypoints1;
    std::vector<Point2f> good_keypoints2;
    for (size_t i = 0; i < good_matches.size(); i++) {
      good_keypoints1.push_back(keypoints1[good_matches[i].queryIdx].pt);
      good_keypoints2.push_back(keypoints2[good_matches[i].trainIdx].pt);
    }

    std::vector<int> mask;
    Mat H = findHomography(good_keypoints1, good_keypoints2, RANSAC, 3, mask);
    double translation = 0;
    int count = 0;
    for (int i = 0; i < mask.size(); ++i) {
      if (mask[i] == 1) {
        translation += good_keypoints1[i].x - good_keypoints2[i].x;
        ++count;
      }
    }
    translation /= count;
    int i_tr = (int)translation;
    Mat first_half =
        stitched(Range::all(), Range(col_offset, col_offset + im1.cols));
    Mat second_half = stitched(
        Range::all(), Range(col_offset + i_tr, col_offset + im1.cols + i_tr));

    im1.copyTo(first_half);
    im2.copyTo(second_half);
    return i_tr;
  }
  std::cout << "Warning: some images couldn't be stitched, trying to stitch "
               "the others anyway"
            << std::endl;
  return 0;
}
Mat ImageStitcher::stitch() {
  int rows = imgs[0].rows;
  int cols = 0;
  for (int i = 0; i < imgs.size(); ++i) {
    cols += imgs[i].cols;
  }
  Mat stitched = Mat(rows, cols, imgs[0].type());
  int col_offset = 0;
  for (int i = 0; i < imgs.size() - 1; ++i) {
    col_offset += stitch_two_images(imgs[i], imgs[i + 1], stitched, col_offset);
  }
  stitched = stitched(Range::all(), Range(0, col_offset));
  return stitched;
}
