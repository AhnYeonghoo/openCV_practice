#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat();
	cout << mat << endl;
}

int main_input_array_op()
{
	uchar data1[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat1(2, 3, CV_8U, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
	return 0;
}

