#include <opencv2/opencv.hpp>
#include <iostream>

void mainfist()
{
	cv::Mat image(300, 400, CV_8UC1, cv::Scalar(200));
	cv::imshow("���󺸱�", image);
	cv::waitKey(0);
}