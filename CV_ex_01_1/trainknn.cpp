#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
using namespace cv::ml;

Ptr<KNearest> trainKnn()
{
	Mat digits = imread("digits.png", IMREAD_GRAYSCALE);
	
	if (digits.empty())
	{
		cerr << "Image load failed!" << endl;
		return 0;
	}
	
	Mat train_images, train_labels;
	
	for (int j = 0; j < 50; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			Mat roi, roi_float, roi_flatten;
			roi = digits(Rect(i * 20, j * 20, 20, 20));
			roi.convertTo(roi_float, CV_32F);
			roi_flatten = roi_float.reshape(1, 1);

			train_images.push_back(roi_flatten);
			train_labels.push_back(j / 5);
		}
	}
	
	Ptr<KNearest> knn = KNearest::create();
	knn->train(train_images, ROW_SAMPLE, train_labels);

	return knn;
}

Point pt_prev(-1, -1);

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;
	
	if (event == EVENT_LBUTTONDOWN)
	{
		pt_prev = Point(x, y);
	}
	else if (event == EVENT_LBUTTONUP)
	{
		pt_prev = Point(-1, -1);
	}
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		line(img, pt_prev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
		pt_prev = Point(x, y);

		imshow("img", img);
	}
}

int main()
{
	Ptr<KNearest> knn = trainKnn();
	
	if (knn.empty())
	{
		cerr << "traning failed! " << endl;
		return -1;
	}
	
	Mat img = Mat::zeros(400, 400, CV_8U);
	
	imshow("Img", img);
	setMouseCallback("img", onMouse, (void*)&img);
	
	while (true)
	{
		int c = waitKey();
		
		if (c == 27)
			break;
		else if (c == ' ')
		{
			Mat img_resize, img_float, img_flatten, res;
			
			resize(img, img_resize, Size(20, 20), 0, 0,INTER_AREA);
			img_resize.convertTo(img_float, CV_32F);
			img_flatten = img_float.reshape(1, 1);
			
			knn->findNearest(img_flatten, 3, res);
			cout << cvRound(res.at<float>(0, 0)) << endl;
			
			img.setTo(0);
			imshow("img", img);

		}
	}
	return 0;
}