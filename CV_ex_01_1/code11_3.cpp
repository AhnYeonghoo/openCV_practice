#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void erodeDilate()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());
	
	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);
	waitKey();
	destroyAllWindows();
}

void openClose()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	
	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());
	
	imshow("src", src);
	imshow("bin", bin);
	imshow("opening", dst1);
	imshow("Closing", dst2);
	waitKey();
	destroyAllWindows();
}

void labelingBasic()
{
	uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0 ,0 ,0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};
	
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;
	
	Mat labels;
	int cnt = connectedComponents(src, labels);
	
	cout << "src\n" << src << endl;
	cout << "labels:\n" << labels << endl;
	cout << "number of labels: " << cnt << endl;
}

void labelingStats()
{
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	
	for (int i = 1; i < cnt; i++)
	{
		int* p = stats.ptr<int>(i);
		if (p[4] < 20) continue;
		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void contoursBasic()
{
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, i, c, 2);
	}
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void contoursHier()
{
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	
	for (int i = 0; i >= 0; i = hierarchy[i][0])
	{
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, i, c, -1, LINE_8, hierarchy);
	}
	
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void setLabel(Mat& img, const vector<Point>& pts, const String& label)
{
	Rect rc = boundingRect(pts);
	rectangle(img, rc, Scalar(0, 0, 255), 1);
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

int maincode11()
{
	//erodeDilate();
	//openClose();
	//labelingBasic();
	//labelingStats();
	//contoursBasic();
	
	Mat img = imread("polygon.bmp", IMREAD_COLOR);
	
	if (img.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	
	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);
	
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	
	for (vector<Point>& pts : contours)
	{
		if (contourArea(pts) < 400)
			continue;
		
		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);
		
		int vtc = (int)approx.size();
		
		if (vtc == 3)
		{
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4)
		{
			setLabel(img, pts, "RECT");
		}
		else if (vtc > 4)
		{
			double len = arcLength(pts, true);
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);
			
			if (ratio > 0.8)
			{
				setLabel(img, pts, "CIR");
			}
		}
	}

	imshow("img", img);
	waitKey();
	return 0;
}
