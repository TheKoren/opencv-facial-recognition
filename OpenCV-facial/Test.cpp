#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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

int main()
{
    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat dst;

    if (img.empty())
    {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    int choice;
    cout << "Select desired operation on image:\n";
    cout << "1. Median filter\n";
    cout << "2. Edge detection\n";
    cout << "3. Gray scale color conversion\n";
    cout << "4. Gaussian blur\n";
    cout << "5. Image sharpening\n";
    cout << "6. Histogram equalization\n";
    cout << "7. Brightness and contrast adjustment\n";
    cout << "8. Sobel edge detection\n";
    cout << "9. Laplacian edge detection\n";
    cout << "10. Dilation\n";
    cout << "11. Erosion\n";
    cout << "12. Cartoon effect\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        medianBlur(img, dst, 5);
        imshow("Median Filter", dst);
        break;
    case 2:
        Canny(img, dst, 100, 200);
        imshow("Edge Detection", dst);
        break;
    case 3:
        cvtColor(img, dst, COLOR_BGR2GRAY);
        imshow("Grayscale", dst);
        break;
    case 4:
        GaussianBlur(img, dst, Size(15, 15), 0);
        imshow("Gaussian Blur", dst);
        break;
    case 5:
    {
        Mat kernel = (Mat_<float>(3, 3) <<
            0, -1, 0,
            -1, 5, -1,
            0, -1, 0);
        filter2D(img, dst, CV_32F, kernel);
        dst.convertTo(dst, CV_8U);
        imshow("Image Sharpening", dst);
    }
    break;
    case 6:
        cvtColor(img, dst, COLOR_BGR2GRAY);
        equalizeHist(dst, dst);
        imshow("Histogram Equalization", dst);
        break;
    case 7:
    {
        double alpha;
        int beta;
        cout << "Enter alpha (contrast, 1.0-3.0): ";
        cin >> alpha;
        cout << "Enter beta (brightness, 0-100): ";
        cin >> beta;
        adjustBrightnessContrast(img, dst, alpha, beta);
        imshow("Brightness and Contrast Adjustment", dst);
    }
    break;
    case 8:
        sobelEdgeDetection(img, dst);
        imshow("Sobel Edge Detection", dst);
        break;
    case 9:
        laplacianEdgeDetection(img, dst);
        imshow("Laplacian Edge Detection", dst);
        break;
    case 10:
        applyDilation(img, dst);
        imshow("Dilation", dst);
        break;
    case 11:
        applyErosion(img, dst);
        imshow("Erosion", dst);
        break;
    case 12:
        cartoonEffect(img, dst);
        imshow("Cartoon Effect", dst);
        break;
    default:
        cout << "Invalid choice!" << endl;
        return -1;
    }

    waitKey(0);
    return 0;
}