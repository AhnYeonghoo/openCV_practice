#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat bgr_img = imread("color_model.jpg", IMREAD_COLOR);
	CV_Assert(bgr_img.data);
	
	Scalar white(255, 255, 255);
	Mat cmy_img = white - bgr_img;
	Mat cmy_arr[3];
	split(cmy_img, cmy_arr);
	
	Mat black;
	min(cmy_arr[0], cmy_arr[1], black);
	min(black, cmy_arr[2], black);

	cmy_arr[0] = cmy_arr[0] - black;
	cmy_arr[1] = cmy_arr[1] - black;
	cmy_arr[2] = cmy_arr[2] - black;
	
	imshow("black", black);
	imshow("yellow", cmy_arr[0]);
	imshow("magenta", cmy_arr[1]);
	imshow("cyan", cmy_arr[2]);
	waitKey();

	return 0;
}