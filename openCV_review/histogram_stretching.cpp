#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void calc_histo4(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
	int hist_size[] = { bins };
	float range[] = { 0, (float)range_max };
	int channels[] = { 0 };
	const float* ranges[] = { range };
	calcHist(&image, 1, channels, Mat(), hist, 1, hist_size, ranges);
}

void draw_histo4(Mat& hist, Mat& hist_img, Size size = Size(256, 200))
{
	hist_img = Mat(size, CV_8U, Scalar(255));
	float bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

	for (int i = 0; i < hist.rows; i++)
	{
		float start_x = i * bin;
		float end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at<float>(i));

		if (pt2.y > 0)
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}

int searchValueIdx(Mat hist, int bias = 0)
{
	for (int i = 0; i < hist.rows; i++)
	{
		int idx = abs(bias - i);
		if (hist.at<float>(idx) > 0) return idx;
	}
	return -1;
}

int main_histogram_stretching()
{
	Mat image = imread("histo_test.jpg", 0);
	CV_Assert(image.data);
	
	Mat hist, hist_dst, hist_img, hist_dst_img;
	int histsize = 64, ranges = 256;
	calc_histo4(image, hist, histsize, ranges);
	
	float bin_width = (float)ranges / histsize;
	int low_value = (int)(searchValueIdx(hist, 0) * bin_width);
	int high_value = (int)(searchValueIdx(hist, hist.rows - 1) * bin_width);
	cout << "High value = " << high_value << endl;
	cout << "low_value = " << low_value << endl;
	
	int d_value = high_value - low_value;
	Mat dst = (image - low_value) * (255.0 / d_value);
	
	calc_histo4(dst, hist_dst, histsize, ranges);
	draw_histo4(hist, hist_img);
	draw_histo4(hist_dst, hist_dst_img);
	
	imshow("image", image); imshow("hist_img", hist_img);
	imshow("dst", dst); imshow("hist_dst_img", hist_dst_img);
	waitKey();
	return 0;
	
}