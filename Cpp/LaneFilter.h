#ifndef CPP_LANEFILTER_H
#define CPP_LANEFILTER_H

#include <opencv2/opencv.hpp>

using namespace cv;


class LaneFilter {
private:
  //Gaussian Blur
  Size Gaussian_kernel_size = Size(3,3);
  double Gaussian_sigmaX = 0;
  double Gaussian_sigmaY = 0;
  int Gaussian_border_type = BORDER_DEFAULT;

  //Canny EdgeDetection
  double lower_threshold = 150;
  double upper_threshold = 200;
  int aperture_size = 3;
  bool L2_gradient = false;

  //Color Thresholding
  int yellow_lower_H = 20;
  int yellow_higher_H = 30;
  int yellow_lower_S = 100;
  int yellow_higher_S = 255;
  int yellow_lower_V = 100;
  int yellow_higher_V = 255;

  int white_lower_L = 185;
  int white_higher_L = 255;

public:
  Mat GrayFromBGR(Mat InputImage);
  Mat HSVfromBGR(Mat InputImage);
  Mat HLSfromBGR(Mat InputImage);
  Mat ColorThreshold(Mat InputImage, Scalar lower, Scalar higher);
  Mat DeNoise(Mat InputImage);
  Mat ROI(Mat InputImage);
  Mat EdgeDetection(Mat InputImage); // Input is in Grey scale
  Mat operator()(Mat InputImage);
    // LaneFilter(); //Custom Constructor
    // ~LaneFilter(); //Destructor, must release all objects/pointers
    //
    // void applyFilter();

    // void hsvFilter();
    // void grayFilter();
    // void CannyGradientFilter();
    //
    // /* Example : this is an example code, please follow this guidline
    //  * @param input_ : some input
    //  * @param out_: some output (explain the param)
    //  */
    // void Example(int input_, int &out_);

};


#endif
