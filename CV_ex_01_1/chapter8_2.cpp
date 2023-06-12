#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Point2f srcquad[4], dstquad[4];
Mat src;

void onMouse2(int event, int x, int y, int flags, void* userdata)
{
	static int cnt = 0;
	if (event == EVENT_LBUTTONDOWN)
	{
		if (cnt < 4)
		{
			srcquad[cnt++] = Point2f(x, y);
			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
			
			imshow("src", src);
			
			if (cnt == 4)
			{
				int w = 200, h = 300;
				dstquad[0] = Point2f(0, 0);
				dstquad[1] = Point2f(w-1, 0);
				dstquad[2] = Point2f(w-1, h-1);
				dstquad[3] = Point2f(0, h-1);
				Mat pers = getPerspectiveTransform(srcquad, dstquad);
				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h));
				
				imshow("dst", dst);
			}
		}
	}
}

int mainchapter8_2()
{
	src = imread("card.bmp");

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("src");
	setMouseCallback("src", onMouse2);
	imshow("src", src);
	waitKey();
	return 0;
}