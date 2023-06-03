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

void histotramEqualization()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

void arithmetic()
{
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty())
	{
		cerr << "image load failed!" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	add(src1, src2, dst1);
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
	subtract(src1, src2, dst3);
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

}

void logical()
{
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty())
	{
		cerr << "image load failed" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	bitwise_and(src1, src2, dst1);
	bitwise_or(src1, src2, dst2);
	bitwise_xor(src1, src2, dst3);
	bitwise_not(src1, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();
	destroyAllWindows();

}

void filterEmbossing()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void blurringMean()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "image load failed!" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;

	for (int ksize = 3; ksize <= 7; ksize += 2)
	{
		blur(src, dst, Size(ksize, ksize));
		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void blurringGaussian()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++)
	{
		GaussianBlur(src, dst, Size(), (double)sigma);

		String text = format("sigma = %d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
	
}

void unsharpMask()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);
	for (int i = 1; i <= 5; i++)
	{
		Mat blurred;
		GaussianBlur(src, blurred, Size(), i);
		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;
		String desc = format("sigma: %d", i);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_COMPLEX,
			1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void noise()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);
	for (int i = 10; i <= 30; i += 10)
	{
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, i);
		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);
		String desc = format("i=%d", i);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_COMPLEX, 1.0,
			Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void filterBilareral()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "image load failed!" << endl;
		return;
	}
	
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);
	
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();

}

void filterMedian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "image load failed!" << endl;
		return;
	}
	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++)
	{
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);
	Mat dst2;
	medianBlur(src, dst2, 3);
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
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
	//histogramStretching();
	//histotramEqualization();
	//arithmetic();
	//logical();
	//filterEmbossing();
	//blurringMean();
	//blurringGaussian();
	//unsharpMask();
	//noise();
	//filterBilareral();
	filterMedian();

	return 0;
}