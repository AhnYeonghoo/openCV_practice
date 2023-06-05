#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void sobelEdge()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag);
	fmag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

void cannyEdge()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	
	waitKey();
	destroyAllWindows();
}

void houghLines()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);
	
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);
	
	for (size_t i = 0; i < lines.size(); i++)
	{
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;
		
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void houghLineSegments()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);
	
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);
	
	for (Vec4i l : lines)
	{
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255),
			2, LINE_AA);
	}
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void houghCircles()
{
	Mat src = imread("coins.png", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3));
	
	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles)
	{
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void colorInverse()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());
	
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			Vec3b& p1 = src.at<Vec3b>(i, j);
			Vec3b& p2 = dst.at<Vec3b>(i, j);

			p2[0] = 255 - p1[0];
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void colorGrayscale()
{
	Mat src = imread("butterfly.jpg");

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void colorSplit()
{
	Mat src = imread("candies.png");
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	
	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);
	
	waitKey();
	destroyAllWindows();
}

void coloreq()
{
	Mat src = imread("pepper.bmp", IMREAD_COLOR);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat src_ycrcb;
	
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	
	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);
	
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);
	
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);
	
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
}


int mainchapter9()
{
	//sobelEdge();
	//houghLines();
	//houghLineSegments();
	//houghCircles();
	//colorInverse();
	//colorGrayscale();
	//colorSplit();
	coloreq();
	return 0;
}