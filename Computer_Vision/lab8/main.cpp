#include "opencv2/calib3d.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/core/utils/filesystem.hpp>
#include <ostream>
#include <string>
#include <vector>
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char **argv) {
  std::string glob_path("*.jpeg");
  if (argc < 1) {
    cout << "Error, provide path to the directory, the angle and format if "
            "it's not png"
         << endl;
    return -1;
  }
  std::vector<std::string> filenames;
  utils::fs::glob(".", glob_path, filenames);
  std::vector<Mat> imgs;
  imgs.reserve(filenames.size());
  for (int i = 0; i < filenames.size(); ++i) {
    Mat im = imread(filenames[i]);
    imgs.push_back(im);
  }
  cout << imgs.size() << endl;

  std::vector<std::vector<Point3f>> objpoints;
  std::vector<std::vector<Point2f>> vec_of_corners;
  float tile_size = 0.022f;
  std::vector<Point3f> objs;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 6; ++j) {
      objs.push_back(Point3f(i * tile_size, j * tile_size, 0));
    }
  }
  for (auto &im : imgs) {
    std::vector<Point2f> corners;
    bool was_found = findChessboardCorners(im, Size(9, 6), corners);
    drawChessboardCorners(im, Size(9, 6), corners, was_found);
    imshow(std::string(was_found ? "true" : "false"), im);
    waitKey(0);
    vec_of_corners.push_back(corners);
    objpoints.push_back(objs);
  }
  Mat cameraMatrix, distCoeffs, R, T;
  calibrateCamera(objpoints, vec_of_corners, Size(imgs[0].rows, imgs[0].cols),
                  cameraMatrix, distCoeffs, R, T);
  std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
  std::cout << "Rotation vector : " << R << std::endl;
  std::cout << "Dist coeffs: " << distCoeffs << std::endl;
  Mat map1, map2, newCameraMatrix;
  initUndistortRectifyMap(cameraMatrix, distCoeffs, R, newCameraMatrix,
                          Size(imgs[0].rows, imgs[0].cols), CV_32FC1, map1,
                          map2);
  Mat out;
  remap(imgs[0], out, map1, map2, INTER_LINEAR);
  imshow("o", out);

  waitKey(0);
  return 0;
}
