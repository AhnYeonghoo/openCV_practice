#include "opencv2/opencv.hpp"
#include <iostream>


void MatOp1();
void MatOp2();
void MatOp3();

int main()
{
	MatOp1();
	//MatOp2();
	MatOp3();
}

void MatOp1()
{
	cv::Mat img1;
	
	cv::Mat img2(480, 640, CV_8UC1);
	cv::Mat img3(480, 640, CV_8UC3);
	cv::Mat img4(cv::Size(640, 480), CV_8UC3);
	cv::Mat img5(480, 640, CV_8UC1, cv::Scalar(128));
	cv::Mat img6(480, 640, CV_8UC3, cv::Scalar(0, 0, 255));
	
	cv::Mat mat1 = cv::Mat::zeros(3, 3, CV_32SC1);
	cv::Mat mat2 = cv::Mat::ones(3, 3, CV_32FC1);
	cv::Mat mat3 = cv::Mat::eye(3, 3, CV_32FC1);

	float data[] = { 1, 2, 3, 4, 5, 6 };
	cv::Mat mat4(2, 3, CV_32FC1, data);
	
	cv::Mat mat5 = (cv::Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	cv::Mat mat6 = cv::Mat_<uchar>({ 2, 3 }, { 1, 2, 3, 4, 5,6 });
	
	mat4.create(256, 256, CV_8UC3);
	mat5.create(4, 4, CV_32FC1);
	
	mat4 = cv::Scalar(255, 0, 0);
	mat5.setTo(1.f);
	

}

void MatOp2()
{
	cv::Mat img1 = cv::imread("dog.bmp");
	cv::Mat img2 = img1;
	cv::Mat img3;
	img3 = img1;
	
	cv::Mat img4 = img1.clone();
	cv::Mat img5;
	img1.copyTo(img5);
	
	img1.setTo(cv::Scalar(0, 255, 255));
	
	
	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	cv::imshow("img3", img3);
	cv::imshow("img4", img4);
	cv::imshow("img5", img5);
	
	cv::waitKey();
	cv::destroyAllWindows();
}

void MatOp3()
{
	cv::Mat img1 = cv::imread("cat.bmp");
	
	if (img1.empty())
	{
		std::cerr << "Image load failed!" << std::endl;
		return;
	}
	
	cv::Mat img2 = img1(cv::Rect(220, 120, 340, 240));
	cv::Mat img3 = img1(cv::Rect(220, 120, 340, 240)).clone();
	
	img2 = ~img2;
	
	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	cv::imshow("img3", img3);

	cv::waitKey();
	cv::destroyAllWindows();

}