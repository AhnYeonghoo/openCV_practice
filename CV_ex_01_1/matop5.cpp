#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int mainmapop5()
{
	Mat img1 = imread("lenna.bmp");
	
	cout << "width: " << img1.cols << endl; // 행렬의 열이 가로
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;
	
	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image. " << endl;
	else if (img1.type() == CV_8UC3)
		cout << "Img1 is a truecolor image." << endl;

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;

	return 0;
}