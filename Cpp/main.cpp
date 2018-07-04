#include <iostream>
#include "LaneFilter.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char const *argv[]) {
  LaneFilter LF;
  Mat InputImage;
  if (argc == 2) {
    InputImage = imread(argv[1]);
  } else {
    InputImage = imread("../../TestingImages/InputImage.png");
  }
  Mat filtered;
  filtered = LF(InputImage);
  return 0;
  imwrite("../../TestingImages/OutputImage.png", filtered);
}
