#include "LaneFilter.h"

#define DEBUG_MSG(x) std::cout<<x<<std::endl;

using namespace cv;

Mat LaneFilter::GrayFromBGR(const Mat& InputImage)
{
  Mat OutputImage;
  cvtColor(InputImage, OutputImage, CV_BGR2GRAY);
  return OutputImage;
}

Mat LaneFilter::HSVfromBGR(const Mat& InputImage)
{
  Mat OutputImage;
  cvtColor(InputImage, OutputImage, CV_BGR2HSV);
  return OutputImage;
}

Mat LaneFilter::HLSfromBGR(const Mat& InputImage)
{
  Mat OutputImage;
  cvtColor(InputImage, OutputImage, CV_BGR2HLS);
  return OutputImage;
}

Mat LaneFilter::ColorThreshold(const Mat& InputImage, Scalar& lower, Scalar& higher)
{
  Mat OutputImage;
  inRange(InputImage, lower, higher, OutputImage);
  return OutputImage;
}

Mat LaneFilter::DeNoise(const Mat& InputImage)
{
  Mat OutputImage;
  GaussianBlur(InputImage, OutputImage, Gaussian_kernel_size, Gaussian_sigmaX, Gaussian_sigmaY, Gaussian_border_type);
  return OutputImage;
}

Mat LaneFilter::EdgeDetection(const Mat& InputImage)
{
  Mat OutputImage;
  Canny(InputImage, OutputImage, lower_threshold, upper_threshold, aperture_size, L2_gradient);
  return OutputImage;
}

Mat ROI(Mat InputImage)
{
  return InputImage;
}

Mat LaneFilter::operator()(const Mat& InputImage)
{
  if(InputImage.empty())
  {
    DEBUG_MSG("[ERROR::Input image empty!]");
    return Mat();
  }

  //setup threshold
  Scalar yellow_lower = Scalar(yellow_lower_H, yellow_lower_S, yellow_lower_V);
  Scalar yellow_upper = Scalar(yellow_higher_H, yellow_higher_S, yellow_higher_V);
  Scalar white_lower = Scalar(white_lower_L);
  Scalar white_upper = Scalar(white_higher_L);
  //yellow line filter
  Mat yellow_filtered, white_filtered, canny_filtered, Mask;
  yellow_filtered = ColorThreshold(HSVfromBGR(InputImage), yellow_lower, yellow_upper);
  //white line filter
  Mat channel[3];
  split(HLSfromBGR(InputImage), channel);
  white_filtered = ColorThreshold(channel[1], white_lower, white_upper);
  //Canny
  canny_filtered = EdgeDetection(DeNoise(GrayFromBGR(InputImage)));
  bitwise_xor(yellow_filtered, white_filtered, Mask);
  bitwise_and(Mask, canny_filtered, Mask);

  DEBUG_MSG("[SUCCESS::Mask Generated!]");
  return Mask;
}

Mat LaneFilter::ROI(const Mat &InputImage) {
    return Mat();
}
