#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int maincopy()
{
	double data[] = {
		1.1, 2.2, 3.3, 4.4,
		5.5, 6.6, 7.7, 8.9,
		9.9, 10 , 11 , 12
	};
	
	Mat m1(3, 4, CV_64F, data);
	Mat m2 = m1.clone();
	Mat m3, m4;
	m1.copyTo(m3);
	m1.convertTo(m4, CV_8U);

	cout << m1 << endl << endl;
	cout << m2 << endl << endl;
	cout << m3 << endl << endl;
	cout << m4 << endl << endl;
	return 0;
}