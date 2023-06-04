#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void affineTransform()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f srcpts[3], dstpts[3];
	srcpts[0] = Point2f(0, 0);
	srcpts[1] = Point2f(src.cols - 1, 0);
	srcpts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstpts[0] = Point2f(50, 50);
	dstpts[1] = Point2f(src.cols - 100, 100);
	dstpts[2] = Point2f(src.cols - 50, src.rows - 50);
	
	Mat M = getAffineTransform(srcpts, dstpts);
	
	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affineShear()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	double mx = 0.3;

	Mat m = Mat_<double>({ 2,3 }, { 1, mx, 0, 0, 1, 0 });
	Mat dst;
	
	warpAffine(src, dst, m, Size(cvRound(src.cols + src.rows * mx), src.rows));
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void affineTranslation()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat m = Mat_<double>({ 2, 3 }, { 1, 0, 150, 0, 1, 100 });
	Mat dst;
	warpAffine(src, dst, m, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affineScale()
{
	Mat src = imread("rose.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	resize(src, dst2, Size(1920, 1280));
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);
	
	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));
	
	waitKey();
	destroyAllWindows();

}

void affineRotation()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}
	
	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	Mat M = getRotationMatrix2D(cp, 20, 1);
	
	Mat dst;
	warpAffine(src, dst, M, Size());
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void affineFlip()
{
	Mat src = imread("eastsea.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}
	
	imshow("src", src);
	
	Mat dst;
	int flip_code[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++)
	{
		flip(src, dst, flip_code[i]);
		String desc = format("flipCode: %d", flip_code[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_COMPLEX,
			1.0, Scalar(255, 0, 0), LINE_AA);
		
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

int mainchapter8_1()
{
	//affineTransform();
	//affineTranslation();
	//affineShear();
	affineScale();
	return 0;
}