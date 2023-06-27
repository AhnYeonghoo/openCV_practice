#include <opencv2/opencv.hpp>
using namespace cv;

int main_circle_draw()
{
	int width = 500;
	int height = 500;
	
	Mat img(height, width, CV_8UC1, Scalar(0, 0, 0));
	
	circle(img, Point(250, 250), 10, Scalar(255, 0, 0), -1);
	circle(img, Point(250, 250), 100, Scalar(0, 0, 255), 1);
	
	imshow("result", img);
	waitKey(0);
	return 0;
}