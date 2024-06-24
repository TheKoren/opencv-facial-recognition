#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "image_processing.h"

using namespace cv;
using namespace std;

int main()
{
    string path = "Resources/test.png";
    Mat img = imread(path);

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

    processImage(img, choice);

    return 0;
}
