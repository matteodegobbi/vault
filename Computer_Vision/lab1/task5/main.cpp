#include <cstddef>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
constexpr size_t grad_mat_size = 256;
constexpr size_t chess_mat_size = 300;
constexpr size_t small_tile = 20;
constexpr size_t big_tile = 50;

void chess_board(cv::Mat &board, size_t tile_size) {
  for (size_t i = 0; i < chess_mat_size; i++) {
    for (size_t j = 0; j < chess_mat_size; j++) {
      if ((j % (2 * tile_size) < tile_size &&
           i % (2 * tile_size) < tile_size) ||
          (j % (2 * tile_size) > tile_size &&
           i % (2 * tile_size) > tile_size)) {
        board.at<uchar>(i, j) = 255;
      } else {
        board.at<uchar>(i, j) = 0;
      }
    }
  }
}
int main(int argc, char **argv) {
  cv::Mat v_grad(grad_mat_size, grad_mat_size, CV_8UC1);
  cv::Mat h_grad(grad_mat_size, grad_mat_size, CV_8UC1);
  for (size_t i = 0; i < grad_mat_size; i++) {
    for (size_t j = 0; j < grad_mat_size; j++) {
      v_grad.at<uchar>(i, j) = i;
      h_grad.at<uchar>(i, j) = j;
    }
  }
  cv::Mat chess20(chess_mat_size, chess_mat_size, CV_8UC1);
  cv::Mat chess50(chess_mat_size, chess_mat_size, CV_8UC1);
  cv::Mat chess100(chess_mat_size, chess_mat_size, CV_8UC1);
  chess_board(chess20, small_tile);
  chess_board(chess50, big_tile);
  chess_board(chess100, 100);
  cv::imshow("vgrad", v_grad);
  cv::imshow("hgrad", h_grad);
  cv::imshow("chess20", chess20);
  cv::imshow("chess50", chess50);
  cv::imshow("chess100", chess100);
  char key = cv::waitKey(0);

  return 0;
}
