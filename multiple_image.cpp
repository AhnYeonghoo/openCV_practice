#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int maintt()
{
	Mat img;
	
	for (int i = 0; i < 21; i++)
	{
		img = imread("./20200504/ok/*.jpg");
		imshow("img", img);
		waitKey(0);
	}

	
	return 0;
}