#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int mainscalarop()
{
	Scalar gray = 128;
	cout << "gray: " << gray << endl;

	Scalar yellow(0, 255, 255);

	cout << "yellow: " << yellow << endl;

	Mat img1(256, 256, CV_8UC3, yellow);
	
	for (int i = 0; i < 4; i++)
		cout << yellow[i] << endl;
	return 0;
}