#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void onThreshold(int pos, void* userdata);


int mainchapter11(int argc, char* argv[])
{
	Mat src;

	if (argc < 2)
	{
		src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	}
	else
	{
		src = imread(argv[1], IMREAD_GRAYSCALE);
	}

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, onThreshold, (void*)&src);
	setTrackbarPos("Threshold", "dst", 128);
	waitKey();
	return 0;
}

void onThreshold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);
	imshow("dst", dst);
}