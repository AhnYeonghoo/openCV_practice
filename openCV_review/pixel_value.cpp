#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main_pixel_value()
{
	Mat image = imread("pixel_test.jpg", IMREAD_GRAYSCALE);
	if (image.empty())
	{
		cerr << "������ ���� ���߽��ϴ�" << endl;
		exit(1);
	}
	
	Rect roi(135, 95, 20, 15); // ���ɿ��� �簢��
	Mat roi_img = image(roi); // ���ɿ��� ����
	cout << "[roi_img] = " << endl;

	for (int i = 0; i < roi_img.rows; i++)
	{
		for (int j = 0; j < roi_img.cols; j++)
		{
			cout.width(5);
			cout << (int)roi_img.at<uchar>(i, j);
		}
		cout << endl;
	}

	rectangle(image, roi, Scalar(255), 1);
	imshow("image", image);
	waitKey(0);
	return 0;
}