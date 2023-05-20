#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>


using namespace std;
using namespace cv;

void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

int main()
{
	//MatOp1();
	//MatOp2();
	//MatOp3();
	//MatOp4();
	//MatOp5();
	//MatOp6();
	//MatOp7();
	Mat image;
	image = imread("cat.bmp", IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);

	waitKey(0);
	

	return 0;
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

void MatOp4()
{
	cv::Mat mat1 = cv::Mat::zeros(3, 4, CV_8UC1);
	
	for (int j = 0; j < mat1.rows; j++)
	{
		for (int i = 0; i < mat1.cols; i++)
		{
			mat1.at<uchar>(j, i)++;
		}
	}

	for (int j = 0; j < mat1.rows; j++)
	{
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++)
		{
			p[i]++;
		}
	}
	
	for (cv::MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it)
	{
		(*it)++;
	}

	std::cout << "mat1:\n" << mat1 << std::endl;

}

void MatOp5()
{
	cv::Mat img1 = cv::imread("lenna.bmp");
	
	std::cout << "width: " << img1.cols << std::endl;
	std::cout << "Height: " << img1.rows << std::endl;
	std::cout << "Channels: " << img1.channels() << std::endl;
	
	if (img1.type() == CV_8UC1)
	{
		std::cout << "img5 is a grayscale image. " << std::endl;
	} 
	else if (img1.type() == CV_8UC3)
	{
		std::cout << "img5 is truecolor image." << std::endl;
	}
	
	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	cv::Mat mat1(2, 2, CV_32FC1, data);
	std::cout << "mat1:\n" << mat1 << std::endl;
}

void MatOp6()
{
	float data[] = { 1, 1, 2, 3 };
	cv::Mat mat1(2, 2, CV_32FC1, data);
	std::cout << "mat1:\n" << mat1 << std::endl;
	
	cv::Mat mat2 = mat1.inv();
	std::cout << "mat2:\n" << mat2 << std::endl;
	
	std::cout << "mat1.t(): \n" << mat1.t() << std::endl;
	std::cout << "mat1 + mat2:\n" << mat1 + mat2 << std::endl;
	std::cout << "mat1 * mat2:\n" << mat1 * mat2 << std::endl;
}

void MatOp7()
{
	cv::Mat img1 = cv::imread("lenna.bmp", cv::IMREAD_GRAYSCALE);
	cv::Mat img1f;
	
	img1.convertTo(img1f, CV_32FC1);
	
	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	cv::Mat mat1(3, 4, CV_8UC1, data1);
	cv::Mat mat2 = mat1.reshape(0, 1);
	
	std::cout << "Mat1:\n" << mat1 << std::endl;
	std::cout << "Mat2:\n" << mat2 << std::endl;
	
	cv::Mat mat3 = cv::Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	
	std::cout << "mat1:\n" << mat1 << std::endl;
	mat1.resize(6, 100);
	std::cout << "mat1:\n" << mat1 << std::endl;
}