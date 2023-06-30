#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void bgr2hsi(Mat img, Mat& hsi)
{
	hsi = Mat(img.size(), CV_32FC3);
	
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float B = img.at<Vec3b>(i, j)[0];
			float G = img.at<Vec3b>(i, j)[1];
			float R = img.at<Vec3b>(i, j)[2];

			float s = 1 - 3 * min(R, min(G, B)) / (R + B + G);
			float v = (R + G + B) / 3.0f;
			
			float tmp1 = ((R - G) + (R - B)) * 0.5f;
			float tmp2 = sqrt((R - G) * (R - B) + (G - B) * (G - B));
			float angle = acos(tmp1 / tmp2) * (180.f / CV_PI);
			float h = (B <= G) ? angle : 360 - angle;

			hsi.at<Vec3f>(i, j) = Vec3f(h / 2, s * 255, v);
		}
	}
	hsi.convertTo(hsi, CV_8U);
}

int main_convert_HSV()
{
	Mat bgr_img = imread("color_space.jpg", IMREAD_COLOR);
	CV_Assert(bgr_img.data);
	Mat hsi_img, hsv_img, hsi[3], hsv[3];

	bgr2hsi(bgr_img, hsi_img);
	cvtColor(bgr_img, hsv_img, COLOR_BGR2HSV);
	split(hsi_img, hsi);
	split(hsv_img, hsv);

	return 0;
}