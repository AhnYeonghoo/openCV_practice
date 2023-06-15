#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int mainrect()
{
	Size2d sz(100.5, 60.6);
	Point2f pt1(20.f, 30.f), pt2(100.f, 200.f);
	
	Rect_<int> rect1(10, 10, 30, 50);
	Rect_<float> rect2(pt1, pt2);
	Rect_<double> rect3(Point2d(20.5, 10), sz);
	
	Rect rect4 = rect1 + (Point)pt1; // 시작좌표를 변경한다. 평행이동
	Rect2f rect5 = rect2 + (Size2f)sz; // 사각형 덧셈 -> 크기 변경
	Rect2d rect6 = rect1 & (Rect)rect2; // 두 사각형의 교집합
		
	cout << "rect3" << rect3.x << ", " << rect3.y << ", " << rect3.width << "x" << rect3.height << endl;
	cout << "rect4 = " << rect4.tl() << " " << rect4.br() << endl;
	cout << "rect5 크기 = " << rect5.size() << endl;
	cout << "[rect6] = " << rect6 << endl;

	return 0;
}