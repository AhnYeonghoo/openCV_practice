#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int mainmat()
{
	float data[] =
	{
		1.2f, 2.3f, 3.2f,
		4.5f, 5.f, 6.5f,
	};
	
	Mat m1(2, 3, CV_8U); // 2�� 3���� unsigned char�� 0 ~ 255
	Mat m2(2, 3, CV_8U, Scalar(300)); // m1�� �����ѵ� 300���� �ʱ�ȭ�ϹǷ� 255
	Mat m3(2, 3, CV_16S, Scalar(300)); // short������ 300���� �ʱ�ȭ
	Mat m4(2, 3, CV_32F, data);
	
	Size sz(2, 3); // ���� x ���� ���δ� �� ���δ� ��
	Mat m5(Size(2, 3), CV_64F);
	Mat m6(sz, CV_32F, data);
	
	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;
	cout << "[m3] = " << endl << m3 << endl;
	cout << "[m4] = " << endl << m4 << endl;
	cout << "[m5] = " << endl << m5 << endl;
	cout << "[m6] = " << endl << m6<< endl;
	return 0;
}