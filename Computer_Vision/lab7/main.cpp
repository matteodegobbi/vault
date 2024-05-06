#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <opencv2/core/utils/filesystem.hpp>
#include <ostream>
#include <string>

#include "ImageStitcher.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char **argv) {
  std::string glob_path("*.");
  if (argc < 3) {
    cout << "Error, provide path to the directory, the angle and format if "
            "it's not png"
         << endl;
    return -1;
  } else if (argc < 4) {
    glob_path.append("png");
  } else {
    glob_path.append(argv[3]);
  }
  ImageStitcher stitcher{argv[1], glob_path, strtod(argv[2], nullptr)};
  Mat stitched = stitcher.stitch();
  equalizeHist(stitched, stitched);
  imshow("Stitched Image", stitched);
  std::string f(argv[1]);
  f.append(".png");
  imwrite(f, stitched);
  waitKey(0);
  return 0;
}
