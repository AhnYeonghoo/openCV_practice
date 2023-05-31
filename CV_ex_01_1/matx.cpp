#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int mainmatx()
{
	Matx<int, 3, 3>		m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	Matx<float, 2, 3>	m2(1, 2, 3, 4, 5, 6);
	Matx<double, 3, 5>	m3(3, 4, 5, 7);
	
	Matx23d m4(3, 4, 5, 6, 7, 8);
	Matx34d m5(1, 2, 3, 10, 11, 12, 13, 14, 15);
	Matx66f m6(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	
	cout << "m5(0,0) = " << m5(0, 0) << " m5(1,0) = " <<
		m5(1, 0) << endl;
	cout << "[m1] =" << endl << m1 << endl;
	cout << "[m5] =" << endl << m5 << endl;
	cout << "[m6] =" << endl << m6 << endl;
	return 0;
}