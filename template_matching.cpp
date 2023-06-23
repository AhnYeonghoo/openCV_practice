#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using namespace cv;

Mat img, templ, mask, result;
int match_method;
bool use_mask;

void matchingMethod(int, void*);

int main()
{
	img = imread("./classification1.bmp", IMREAD_GRAYSCALE);
	templ = imread("./template.bmp", IMREAD_GRAYSCALE);
	/*resize(templ, templ, Size(669, 565));*/
	if (img.empty() || templ.empty())
	{
		cerr << "Image load failed" << endl;
		return -1;
	}
	
	namedWindow("Source Image", WINDOW_AUTOSIZE);
	namedWindow("Result Image", WINDOW_AUTOSIZE);

	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, "Source Image", &match_method, 5, matchingMethod);
	
	matchingMethod(0, 0);

	return 0;

}

void matchingMethod(int, void*)
{
	Mat img_display;
	img.copyTo(img_display);
	
	cvtColor(img_display, img_display, COLOR_GRAY2BGR);

	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	
	result.create(result_rows, result_cols, CV_32FC1);
	
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	
	double min_val, max_val;
	Point min_loc, max_loc;
	Point match_loc;
	double threshold = 0.1;

	minMaxLoc(result, &min_val, NULL, &min_loc, NULL);
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			if (result.at<float>(i, j) < threshold)
			{
				rectangle(img_display, Point(j, i), Point(j + templ.cols, i + templ.rows),
					Scalar(0, 0, 255), 1);
			}
		}
	}
	resize(img_display, img_display, Size(555, 555), 0.15, 0.15, INTER_AREA);
	resize(result, result, Size(555, 555), 0.15, 0.15, INTER_AREA);
	imshow("Source Image", img_display);
	imshow("result image", result);
	imshow("templ", templ);
	waitKey(0);




	//for (int k = 1; k <= 5; k++)
	//{
	//	minMaxLoc(result, &min_val, NULL, &min_loc, NULL);
	//	//minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc, Mat());
	//	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	//	{
	//		result.at<float>(min_loc.x, min_loc.y) = 1.0;
	//		result.at<float>(max_loc.x, max_loc.y) = 1.0;
	//	}
	//	else
	//	{
	//		result.at<float>(min_loc.x, min_loc.y) = 0.0;
	//		result.at<float>(max_loc.x, max_loc.y) = 0.0;
	//	}

	//	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	//	{
	//		match_loc = min_loc;
	//	}
	//	else
	//	{
	//		match_loc = max_loc;
	//	}
	//	
	//	rectangle(img_display, match_loc, Point(match_loc.x + templ.cols, match_loc.y + templ.rows), Scalar(0, 0, 255), 5, 8, 0);
	//	rectangle(result, match_loc, Point(match_loc.x + templ.cols, match_loc.y + templ.rows), Scalar(0, 0, 255), 5, 8, 0);
	//	resize(img_display, img_display, Size(555, 555), 0.15, 0.15, INTER_AREA);
	//	resize(result, result, Size(555, 555), 0.15, 0.15, INTER_AREA);
	//	imshow("Source Image", img_display);
	//	
	//}

	
	
	
	
	return;
}

 
//int main()
//{
//    cv::Mat image = cv::imread("classification1.bmp");  // 대상 이미지 로드
//    cv::Mat templ = cv::imread("template.bmp");  // 템플릿 이미지 로드
//   
//    
//    cv::Mat result;
//    cv::matchTemplate(image, templ, result, cv::TM_CCOEFF_NORMED);
//
//    double threshold = 0.01;  // 유사도 임계값 설정
//    double maxVal;
//    cv::Point maxLoc;
//
//    std::vector<cv::Rect> objectLocations;
//
//    while (true)
//    {
//        cv::minMaxLoc(result, nullptr, &maxVal, nullptr, &maxLoc);
//
//        if (maxVal >= threshold)
//        {
//            cv::Rect objectLocation(maxLoc, cv::Size(templ.cols, templ.rows));
//            objectLocations.push_back(objectLocation);
//            cv::floodFill(result, maxLoc, cv::Scalar(0), nullptr, cv::Scalar(0.1), cv::Scalar(1.0));
//        }
//        else
//        {
//            break;
//        }
//    }
//
//    // 탐지된 객체를 사각형으로 표시
//    for (const auto& location : objectLocations)
//    {
//        cv::rectangle(image, location, cv::Scalar(0, 0, 255), 2);
//    }
//
//    // 결과 출력
//    resize(image, image, Size(550, 550), 0.1, 0.1);
//
//    cv::imshow("Detected Objects", image);
//    cv::waitKey(0);
//
//    return 0;
//}

//int main()
//{
//	Mat image = imread("classification1.bmp", IMREAD_COLOR);
//	Mat templ = imread("template.bmp", IMREAD_COLOR);
//	
//	if (image.empty() || templ.empty())
//	{
//		cerr << "image load failed!" << endl;
//		return -1;
//	}
//	
//	image = image + Scalar(50, 50, 50);
//	
//	Mat noise(image.size(), CV_32SC3);
//	randn(noise, 0, 10);
//	add(image, noise, image, Mat(), CV_8UC3);
//	
//	Mat res, res_norm;
//	matchTemplate(image, templ, res, TM_CCOEFF_NORMED);
//	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);
//	
//	double maxv;
//	Point maxloc;
//	for (int i = 0; i < 3; i++)
//	{
//		minMaxLoc(res, 0, &maxv, 0, &maxloc);
//		cout << "maxv: " << maxv << endl;
//		rectangle(image, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);
//		resize(image, image, Size(555, 555), 0.2, 0.2, INTER_AREA);
//		imshow("templ", templ);
//		imshow("res_norm", res_norm);
//		imshow("image", image);
//	}
//
//	waitKey(0);
//	destroyAllWindows();
//	return 0;
//}

//int main()
//{
//	Mat image = imread("classification1.bmp", 1);
//	Mat templ = imread("template.bmp", 1);
//	
//	Ptr<Feature2D> feature = ORB::create();
//	
//	vector<KeyPoint> keypoints1, keypoints2;
//	Mat desc1, desc2;
//	feature->detectAndCompute(image, Mat(), keypoints1, desc1);
//	feature->detectAndCompute(templ, Mat(), keypoints2, desc2);
//	
//	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);
//	
//	vector<DMatch> matches;
//	matcher->match(desc1, desc2, matches);
//	
//	std::sort(matches.begin(), matches.end());
//	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);
//	
//	Mat dst;
//	drawMatches(image, keypoints1, templ, keypoints2, good_matches, dst,
//		Scalar::all(-1), Scalar::all(-1), vector<char>(),
//		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
//	resize(dst, dst, Size(555, 555), 0.2, 0.2, INTER_AREA);
//	imshow("dst", dst);
//	waitKey();
//	destroyAllWindows();
//	return 0;
//
//
//}

//int main()
//{
//	Mat img = imread("classification1.bmp", IMREAD_GRAYSCALE);
//	
//	Mat bin;
//	threshold(img, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);
//	
//	vector<vector<Point>> contours;
//	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
//	
//	for (vector<Point>& pts : contours)
//	{
//		if (contourArea(pts) < 400)
//			continue;
//		
//		vector<Point> approx;
//		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);
//		
//		int vtc = (int)approx.size();
//		if (vtc >= 4)
//		{
//			double len = arcLength(pts, true);
//			double area = contourArea(pts);
//			double ratio = 4. * CV_PI * area / (len * len);
//
//			if (ratio > 0.5)
//			{
//				Rect rc = boundingRect(pts);
//				rectangle(img, rc, Scalar(0, 0, 255), 1);
//				putText(img, "Triangle", rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
//			}
//		}
//
//		
//
//	}
//
//	resize(img, img, Size(555, 555), 0.2, 0.2, INTER_AREA);
//	imshow("img", img);
//	waitKey();
//	return 0;
//}