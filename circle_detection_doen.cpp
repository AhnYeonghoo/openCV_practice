#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main_temp()
{
	Mat img = imread("./classification1.bmp", IMREAD_GRAYSCALE);
	
	if (img.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}
    Mat blurred;
    blur(img, blurred, Size(3, 3));

    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

    Mat dst;
    cvtColor(img, dst, COLOR_GRAY2BGR);

    for (Vec3f c : circles) {
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", img);
    imshow("dst", dst);
    imshow("blurred", blurred);

    waitKey(0);
    destroyAllWindows();
	imshow("img", img);
	waitKey(0);

	return 0;
}