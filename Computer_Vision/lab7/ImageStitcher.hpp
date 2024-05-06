#ifndef IMAGE_STITCHER
#define IMAGE_STITCHER
#include <opencv2/core.hpp>
constexpr double percent_of_matches_threshold = 0.03;

class ImageStitcher {
public:
  ImageStitcher(std::string directory, std::string file_extension,
                double angle);
  ~ImageStitcher();
  cv::Mat stitch();

private:
  int stitch_two_images(const cv::Mat &im1, const cv::Mat &im2,
                        cv::Mat &stitched, int col_offset);
  std::vector<cv::Mat> imgs;
};
#endif
