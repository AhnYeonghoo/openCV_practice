#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

void print_matinfo3(string m_name, Mat m)
{
	cout << "[" << m_name << " 행렬]" << endl;
	cout << "  채널 수 =  " << m.channels() << endl;
	cout << "  행 x 열 =  " << m.rows << " x " << m.cols << endl << endl;
}

int mainrelease()
{
	Mat m1(2, 6, CV_8UC1, Scalar(100));
	Mat m2(3, 3, CV_32S);
	Range r1(0, 2), r2(0, 2);
	Mat m3 = m1(r1, r2);

	print_matinfo3("m1", m1);
	print_matinfo3("m3", m3);
	
	m2.release();
	m3.release();
	print_matinfo3("m2", m2);
	print_matinfo3("m3", m3);
	print_matinfo3("m1", m1);
	
	m1.release();
	print_matinfo3("m1", m1);
	return 0;
}