#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int mainmatop4()
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);
	
	for (int i = 0; i < mat1.rows; i++)
	{
		for (int j = 0; j < mat1.cols; j++)
		{
			mat1.at<uchar>(i, j)++;
		}
	}

	for (int i = 0; i < mat1.rows; i++)
	{
		uchar* p = mat1.ptr<uchar>(i);
		for (int j = 0; j < mat1.cols; j++)
		{
			p[j]++;
		}
	}

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); it++)
	{
		(*it)++;
	}
	
	cout << "mat1:\n" << mat1 << endl;
	return 0;
}