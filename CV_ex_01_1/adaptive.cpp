#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void onTrackbar(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	int bsize = pos;
	if (bsize % 2 == 0) bsize--;
	if (bsize < 3) bsize = 3;
	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,
		bsize, 5);
	imshow("dst", dst);
}

int mainadaptive()
{
	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);
	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, onTrackbar, (void*)&src);
	setTrackbarPos("Block Size", "dst", 11);
	waitKey();
	return 0;
}