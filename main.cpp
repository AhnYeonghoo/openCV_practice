#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


void multiple_image()
{
	Mat img;
	Mat gray;
	Mat p_img;
	Mat p_gray;
	
	String path("./20200504/ok/*.jpg");
	
	vector<String> str;
	
	int index = 0;
	char buf[256];

	glob(path, str, false);
	
	cout << str.size() << endl;
	if (str.size() == 0)
	{
		cout << "Image Not Found" << endl;
	}
	
	for (int cnt = 0; cnt < str.size(); cnt++)
	{
		p_img = imread(str[cnt]);
		cvtColor(p_img, p_gray, COLOR_BGR2GRAY);
		index++;
		imwrite(buf, p_gray);
	}
}

int mainttt()
{
	Mat img = imread("./20200504/coating/6_2_1.jpg");
	Mat img_scratch = imread("./20200504/scratch/12_0_0.jpg", 0);
	Mat img_small;
	resize(img, img_small, Size(), 0.4, 0.3);
	Mat img_gray;
	cvtColor(img_small, img_gray, COLOR_BGR2GRAY);
	Mat img_blur;
	Mat img_binary = imread("./20200504/coating/6_2_1.jpg", 0);
	double threshold = 100;
	
	for (int row = 0; row < img_gray.rows; row++)
	{
		for (int col = 0; col < img_gray.cols; col++)
		{
			if (img_gray.at<uchar>(row, col) > threshold)
			{
				img_binary.at<uchar>(row, col) = 0;
			}
			else
			{
				img_binary.at<uchar>(row, col) = 255;
			}
		}
	}

	for (int row = 0; row < img_gray.rows; row++)
	{
		for (int col = 0; col < img_gray.cols; col++)
		{
			if (img_gray.at<uchar>(row, col) > threshold)
			{
				img_scratch.at<uchar>(row, col) = 0;
			}
			else
			{
				img_scratch.at<uchar>(row, col) = 255;
			}
		}
	}

	GaussianBlur(img_gray, img_blur, Size(3, 3), 0);

	if (img.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}
	resize(img_binary, img_binary, Size(), 0.4, 0.4);
	resize(img_scratch, img_scratch, Size(), 0.4, 0.4);
	imshow("img", img_small);
	imshow("img_blur", img_blur);
	imshow("img_binary", img_binary);
	imshow("img_scratch", img_scratch);
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}