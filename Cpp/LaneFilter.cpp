#include "LaneFilter.h"

using namespace cv;

Mat LaneFilter::GrayFromBGR(Mat InputImage)
{
  Mat OutputImage;
  cvtColor(InputImage, OutputImage, CV_BGR2GRAY);
  return OutputImage;
}

Mat LaneFilter::HSVfromBGR(Mat InputImage)
{
  Mat OutputImage;
  cvtColor(InputImage, OutputImage, CV_BGR2HSV);
  return OutputImage;
}

Mat LaneFilter::HLSfromBGR(Mat InputImage)
{
  Mat OutputImage;
  cvtColor(InputImage, OutputImage, CV_BGR2HLS);
  return OutputImage;
}

Mat LaneFilter::ColorThreshold(Mat InputImage, Scalar lower, Scalar higher)
{
  Mat OutputImage;
  inRange(InputImage, lower, higher, OutputImage);
  return OutputImage;
}

Mat LaneFilter::DeNoise(Mat InputImage)
{
  Mat OutputImage;
  GaussianBlur(InputImage, OutputImage, Gaussian_kernel_size, Gaussian_sigmaX, Gaussian_sigmaY, Gaussian_border_type);
  return OutputImage;
}

Mat LaneFilter::EdgeDetection(Mat InputImage)
{
  Mat OutputImage;
  Canny(InputImage, OutputImage, lower_threshold, upper_threshold, aperture_size, L2_gradient);
  return OutputImage;
}

Mat ROI(Mat InputImage)
{
  return InputImage;
}

Mat LaneFilter::operator()(Mat InputImage)
{
  Mat yellow_filtered, white_filtered, canny_filtered, Mask;
  yellow_filtered = ColorThreshold(HSVfromBGR(InputImage)
    , Scalar(yellow_lower_H, yellow_lower_S, yellow_lower_V)
    , Scalar(yellow_higher_H, yellow_higher_S, yellow_higher_V));
  Mat channel[3];
  split(HLSfromBGR(InputImage), channel);
  white_filtered = ColorThreshold(channel[1]
    , Scalar(white_lower_L), Scalar(white_higher_L));
  canny_filtered = EdgeDetection(DeNoise(GrayFromBGR(InputImage)));
  bitwise_xor(yellow_filtered, white_filtered, Mask);
  bitwise_and(Mask, canny_filtered, Mask);
  return Mask;
}
