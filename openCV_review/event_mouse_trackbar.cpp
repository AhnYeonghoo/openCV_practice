#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

string title2 = "밝기변경";
string bar_name = "밝기값";
Mat image2;


void onChange2(int value, void* userdata)
{
	int add_value = value - 130;

	cout << "추가 화소값" << add_value << endl;

	Mat tmp = image2 + add_value;
	imshow(title2, tmp);
}

void onMouse2(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_RBUTTONDOWN)
	{
		add(image2, 10, image2);
		setTrackbarPos(bar_name, title2, image2.at<uchar>(0));
		imshow(title2, image2);
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		subtract(image2, 10, image2);
		setTrackbarPos(bar_name, title2, image2.at<uchar>(0));
		imshow(title2, image2);
	}
}

int main_event_mouse_trackbar()
{
	int value = 130;
	image2 = Mat(300, 500, CV_8UC1, Scalar(120));
	namedWindow(title2, WINDOW_AUTOSIZE);
	createTrackbar(bar_name, title2, &value, 255, onChange2);
	setMouseCallback(title2, onMouse2, 0);
	
	imshow(title2, image2);
	waitKey(0);
	return 0;
}