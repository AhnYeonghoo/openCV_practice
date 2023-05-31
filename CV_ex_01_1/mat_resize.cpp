#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int mainresize()
{
	Mat m = (Mat_<uchar>(2, 4) << 1, 2, 3, 4, 5, 6, 7, 8);
	cout << m << endl << endl;
	
	m.resize(1);
	cout << m << endl << endl;
	m.resize(3);
	cout << m << endl << endl;
	m.resize(5, Scalar(50));
	cout << m << endl << endl;
	
	return 0;
}