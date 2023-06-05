#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int lower_hue = 40, upper_hue = 80;
Mat src2, src_hsv, mask;

void onHueChanged(int, void*);

int maininrange()
{
	src2= imread("candies.png", IMREAD_COLOR);
	
	if (src2.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}
	
	cvtColor(src2, src_hsv, COLOR_BGR2HSV);
	imshow("src", src2);
	
	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, onHueChanged);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, onHueChanged);
	onHueChanged(0, 0);
	
	waitKey();
	return 0;
}

void onHueChanged(int, void*)
{
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}
