#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "image_processing.h"

using namespace cv;
using namespace std;

int main()
{
    int choice;
    string path;
    Mat img;
    cout << "Select input format:\n";
    cout << "1. Image\n";
    cout << "2. Video\n";
    cout << "3. Webcam\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        path = "Resources/test.png";
        img = imread(path);

        if (img.empty())
        {
            cout << "Could not open or find the image!" << endl;
            return -1;
        }

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

    }
    else if (choice == 2)
    {
        path = "Resources/test2.mp4";
        VideoCapture cap(path);

        while (true)
        {
            cap.read(img);
            imshow("Video", img);
            waitKey(10);
        }
    }
    else if (choice == 3)
    {
        VideoCapture cap(0);

        while (true)
        {
            cap.read(img);
            imshow("Video", img);
            waitKey(1);
        }
    }
    else
    {
        return 0;
    }
    

    return 0;
}
