#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main1()
{
	cv::Mat image(300, 400, CV_8UC1, cv::Scalar(200));
	cv::imshow("영상보기", image);
	cv::waitKey(0);

	return 0;
}

