#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

void adjustBrightnessContrast(Mat& src, Mat& dst, double alpha, int beta);
void sobelEdgeDetection(Mat& src, Mat& dst);
void laplacianEdgeDetection(Mat& src, Mat& dst);
void applyDilation(Mat& src, Mat& dst);
void applyErosion(Mat& src, Mat& dst);
void cartoonEffect(Mat& src, Mat& dst);
void medianFilter(Mat& src, Mat& dst);
void edgeDetection(Mat& src, Mat& dst);
void grayScale(Mat& src, Mat& dst);
void gaussianBlur(Mat& src, Mat& dst);
void imageSharpening(Mat& src, Mat& dst);
void histogramEqualization(Mat& src, Mat& dst);
void processImage(Mat& src, int choice);
void resizeCrop(Mat& src, Mat& dst);

#endif // IMAGE_PROCESSING_H
