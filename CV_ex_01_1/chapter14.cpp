#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void corner_harris()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);
	
	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	
	for (int j = 1; j < harris.rows - 1; j++)
	{
		for (int i = 1; i < harris.cols - 1; i++)
		{
			if (harris_norm.at<uchar>(j, i) > 120)
			{
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i)
					&& harris.at<float>(j, i) > harris.at<float>(j + 1, i)
					&& harris.at<float>(j, i) > harris.at<float>(j, i - 1)
					&& harris.at<float>(j, i) > harris.at<float>(j, i + 1))
				{
					circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2);
				}
			}
		}
	}
	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void cornerFast()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}
	
	vector<KeyPoint> keypoints;
	FAST(src, keypoints, 60, true);
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);
	
	for (KeyPoint& kp : keypoints)
	{
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);
	
	waitKey();
	destroyAllWindows();
}

void detectKeypoints()
{
	Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);
	
	if (src.empty())
	{
		cerr << "image load failed!" << endl;
		return;
	}
	
	Ptr<Feature2D> feature = ORB::create();
	
	vector<KeyPoint> keypoints;
	feature->detect(src, keypoints);
	
	Mat desc;
	feature->compute(src, keypoints, desc);
	
	cout << "Keypoints.size(): " << keypoints.size() << endl;
	cout << "desc.size(): " << desc.size() << endl;
	
	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1),
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	
	imshow("src", src);
	imshow("dst", dst);

	waitKey(); 
	destroyAllWindows();
}

void keypointMatching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);
	
	if (src1.empty() || src2.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();


	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);
	
	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);
	
	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);
	
	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);

	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

int main()
{
	//corner_harris();
	//cornerFast();
	detectKeypoints();
	return 0;
}