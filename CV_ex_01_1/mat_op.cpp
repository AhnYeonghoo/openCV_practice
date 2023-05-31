#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main_mat_op()
{
	Mat m1(2, 3, CV_8U, 2);
	Mat m2(2, 3, CV_8U, Scalar(10));
	
	Mat m3 = m1 + m2;
	Mat m4 = m2 - 6;
	Mat m5 = m1;
	
	cout << "[m2]= " << m2 << endl;
	cout << "[m3]= " << m3 << endl;
	cout << "[m4]= " << endl << m4 << endl;

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m5] = " << endl << m5 << endl;
	m5 = 100;
	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m5] = " << endl << m5 << endl;

	return 0;
}