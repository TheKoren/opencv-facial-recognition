#include "image_processing.h"
#include <iostream>

void adjustBrightnessContrast(Mat& src, Mat& dst, double alpha, int beta) {
    src.convertTo(dst, -1, alpha, beta); // dst = alpha*src + beta
}

void sobelEdgeDetection(Mat& src, Mat& dst) {
    Mat gray, grad_x, grad_y;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Sobel(gray, grad_x, CV_16S, 1, 0, 3);
    Sobel(gray, grad_y, CV_16S, 0, 1, 3);
    convertScaleAbs(grad_x, grad_x);
    convertScaleAbs(grad_y, grad_y);
    addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);
}

void laplacianEdgeDetection(Mat& src, Mat& dst) {
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Laplacian(gray, dst, CV_16S, 3);
    convertScaleAbs(dst, dst);
}

void applyDilation(Mat& src, Mat& dst) {
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(src, dst, kernel);
}

void applyErosion(Mat& src, Mat& dst) {
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    erode(src, dst, kernel);
}

void cartoonEffect(Mat& src, Mat& dst) {
    Mat gray, edges, color;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 7);
    Laplacian(gray, edges, CV_8U, 5);
    threshold(edges, edges, 80, 255, THRESH_BINARY_INV);
    bilateralFilter(src, color, 9, 75, 75);
    dst = Scalar::all(0);
    color.copyTo(dst, edges);
}

void medianFilter(Mat& src, Mat& dst) {
    medianBlur(src, dst, 5);
}

void edgeDetection(Mat& src, Mat& dst) {
    Canny(src, dst, 100, 200);
}

void grayScale(Mat& src, Mat& dst) {
    cvtColor(src, dst, COLOR_BGR2GRAY);
}

void gaussianBlur(Mat& src, Mat& dst) {
    GaussianBlur(src, dst, Size(15, 15), 0);
}

void imageSharpening(Mat& src, Mat& dst) {
    Mat kernel = (Mat_<float>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    filter2D(src, dst, CV_32F, kernel);
    dst.convertTo(dst, CV_8U);
}

void histogramEqualization(Mat& src, Mat& dst) {
    cvtColor(src, dst, COLOR_BGR2GRAY);
    equalizeHist(dst, dst);
}

void resizeCrop(Mat& src, Mat& dst) {
    Rect roi(100, 100, 250, 250);
    src = src(roi);
    resize(src, dst, Size(), 0.5, 0.5);
}

void drawingImage(Mat& dst)
{
    Mat img(512, 512, CV_8UC3, Scalar(31, 55, 150));

    circle(img, Point(256, 256), 155, Scalar(0, 0, 0), FILLED);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    putText(img, "Sample", Point(137, 262), FONT_HERSHEY_DUPLEX, 1.85, Scalar(0, 70, 255), 1.5);
    dst = img;
}

void processImage(Mat& src, int choice) {
    Mat dst;
    switch (choice)
    {
    case 1:
        medianFilter(src, dst);
        imshow("Median Filter", dst);
        break;
    case 2:
        edgeDetection(src, dst);
        imshow("Edge Detection", dst);
        break;
    case 3:
        grayScale(src, dst);
        imshow("Grayscale", dst);
        break;
    case 4:
        gaussianBlur(src, dst);
        imshow("Gaussian Blur", dst);
        break;
    case 5:
        imageSharpening(src, dst);
        imshow("Image Sharpening", dst);
        break;
    case 6:
        histogramEqualization(src, dst);
        imshow("Histogram Equalization", dst);
        break;
    case 7:
    {
        double alpha;
        int beta;
        std::cout << "Enter alpha (contrast, 1.0-3.0): ";
        std::cin >> alpha;
        std::cout << "Enter beta (brightness, 0-100): ";
        std::cin >> beta;
        adjustBrightnessContrast(src, dst, alpha, beta);
        imshow("Brightness and Contrast Adjustment", dst);
    }
    break;
    case 8:
        sobelEdgeDetection(src, dst);
        imshow("Sobel Edge Detection", dst);
        break;
    case 9:
        laplacianEdgeDetection(src, dst);
        imshow("Laplacian Edge Detection", dst);
        break;
    case 10:
        applyDilation(src, dst);
        imshow("Dilation", dst);
        break;
    case 11:
        applyErosion(src, dst);
        imshow("Erosion", dst);
        break;
    case 12:
        cartoonEffect(src, dst);
        imshow("Cartoon Effect", dst);
        break;
    case 13:
        resizeCrop(src, dst);
        imshow("Resize and Crop", dst);
    case 14:
        drawingImage(dst);
        imshow("Drawing", dst);
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }
    waitKey(0);
}
