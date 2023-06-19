#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

string title = "트랙바 이벤트";
Mat image;

void onChange(int value, void* userdata)
{
	int add_value = value - 130;
	cout << "추가 화소값 " << add_value << endl;
	Mat temp = image + add_value;
	imshow(title, temp);
}

int main_event_trackbar()
{
	int value = 120;
	image = Mat(300, 400, CV_8UC1, Scalar(120));
	
	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("밝기값", title, &value, 255, onChange);
	imshow(title, image);
	waitKey(0);
	return 0;
}