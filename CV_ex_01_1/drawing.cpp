#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void drawing()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void drawPolys()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));
	
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 120), -1);
	
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);
	
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), -1, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);
	
	vector<Point> pts;
	pts.push_back(Point(250, 250));
	pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300));
	pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350));
	pts.push_back(Point(250, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void drawText1()
{
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));
	
	putText(img, "FONT_hershey_simplex", Point(20, 50),
		FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));

	imshow("img", img);

	waitKey();
}

void drawText2()
{
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));
	
	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;
	Size size_text = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();
	
	Point org((sizeImg.width - size_text.width) / 2,
		(sizeImg.height + size_text.height) / 2);
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	
	rectangle(img, org, org + Point(size_text.width, -size_text.height),
		Scalar(255, 0, 0), 1);
	
	imshow("img", img);
	waitKey();
	destroyAllWindows();
}

int keyboard()
{
	Mat img = imread("lenna.bmp");
	
	if (img.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}
	
	namedWindow("img");
	imshow("img", img);

	while (true)
	{
		int keycode = waitKey();
		
		if (keycode == 'i' || keycode == 'I')
		{
			img = ~img;
			imshow("img", img);
		}
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q')
		{
			break;
		}
	}
	return 0;
}

void mouse(int event, int x, int y, int flags, void*)
{
	Mat img;
	Point ptOld;

	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON)
		{
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}

int maindrawing()
{

	Mat img = imread("lenna.bmp");
	
	if (img.empty())
	{
		cerr << "Image load failed" << endl;
		return -1;
	}
	
	namedWindow("img");
	setMouseCallback("img", mouse);
	
	imshow("img", img);
	waitKey();
	
	//keyboard();
	//drawPolys();
	//drawText1();
	//drawText2();
	return 0;
}

