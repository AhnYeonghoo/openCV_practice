#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int mainmatresize()
{
	Mat m = (Mat_<uchar>(2, 4) << 1, 2, 3, 4, 5, 6, 7, 8);
	cout << "m = " << endl << m << endl << endl;
	
	m.resize(1);
	cout << "m.resize(1) = " << endl << m << endl;
	m.resize(3);
	cout << "m.resize(3) = " << endl << m << endl; 
	m.resize(5, Scalar(5));
	cout << "m.resize(5) = " << endl << m << endl;
	return 0;
}