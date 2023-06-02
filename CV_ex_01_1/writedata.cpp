#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace cv;
using namespace std;

String filename = "mydata.json";

void writeData()
{
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = { 80, 90, 50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);
	
	FileStorage fs(filename, FileStorage::WRITE);
	
	if (!fs.isOpened())
	{
		cerr << "File open failed!" << endl;
		return;
	}
	
	fs <<"name"<<  name;
	fs << "age"<<age;
	fs << "pt1"<<pt1;
	fs << "scores"<<scores;
	fs << "data"<<mat1;

	fs.release();
}

void readData()
{
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;
	
	FileStorage fs(filename, FileStorage::READ);

	if (!fs.isOpened())
	{
		cerr << "File Open failed" << endl;
		return;
	}
	fs["name"] >> name;
	fs["age"] >> age;
	fs["pt1"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;
	
	fs.release();
	
	cout << name << endl;
	cout << age << endl;
	cout << pt1 << endl;
	cout << Mat(scores).t() << endl;
	cout << mat1 << endl;
}

void maskSetTo()
{
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty() || mask.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}
	
	src.setTo(Scalar(0, 255, 255), mask);
	
	imshow("src", src);
	imshow("mask", mask);
	
	waitKey();
	destroyAllWindows();
}

void maskCopyTo()
{
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);
	
	if (src.empty() || mask.empty() || dst.empty()) 
	{
		cerr << "Image load failed" << endl;
		return;
	}

	src.copyTo(dst, mask);
	
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void timeInverse()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "image load failed" << endl;
		return;
	}
	
	Mat dst(src.rows, src.cols, src.type());
	
	TickMeter tm;
	tm.start();
	
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop();
	cout << "Image inverse took" << tm.getTimeMilli() << "ms " << endl;
}

void brightness1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat dst = src + 100;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "image load failed" << endl;
		return;
	}
	
	Mat dst(src.rows, src.cols, src.type());
	
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}
	
	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness3()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}
	
	Mat dst(src.rows, src.cols, src.type());
	
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;
	imshow("dst", dst);
}

void brightness4()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void contrast1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "image load failed" << endl;
		return;
	}
	
	float s = 2.f;
	Mat dst = s * src;
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void contrast2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

Mat calcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };
	
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	return hist;
}

Mat getGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);
	
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++)
	{
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));

	}
	return imgHist;
}

void histogramStretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	
	Mat dst = (src - gmin) * 255 / (gmax - gmin);
	
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);

	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));
	waitKey();
	destroyAllWindows();
}

int main()
{

	//writeData();
	//readData();
	//maskSetTo();
	//maskCopyTo();
	//timeInverse();
	//brightness1();
	//brightness2();
	//brightness3();
	//brightness4();
	//contrast1();

	histogramStretching();

	return 0;
}