#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int mainbackpro()
{
	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);
	
	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128;
	int cb_bins = 128;
	int hist_size[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };
	
	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, hist_size, ranges);
	
	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	
	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);
	
	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();
	return 0;
}