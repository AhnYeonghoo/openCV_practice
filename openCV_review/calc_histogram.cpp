#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void calc_histo(Mat image, Mat& hist, int bins, int range_max = 256)
{
	hist = Mat(bins, 1, CV_32F, Scalar(0)); // 히스토그램 누적 해열ㄹ
	float gap = range_max / (float)bins;
	
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int idx = int(image.at<uchar>(i, j) / gap);
			hist.at<float>(idx)++;
		}
	}
}

int main_calc_histogram()
{
	Mat image = imread("pixel_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);
	
	Mat hist;
	calc_histo(image, hist, 256);
	cout << hist.t() << endl;
	imshow("image", image);
	waitKey();
	return 0;
}