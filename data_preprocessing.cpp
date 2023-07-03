#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	//Mat src = imread("./ccm/coating/6_0_2.jpg", IMREAD_GRAYSCALE);
	//Mat denoise;
	//fastNlMeansDenoising(src, denoise, 7.0, 7, 21);
	//
	////Mat target_image = imread("template.bmp", IMREAD_GRAYSCALE);
	//
	//if (src.empty())
	//{
	//	std::cerr << "Image Load Failed" << std::endl;
	//	return -1;
	//}

	//Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();
	//
	//vector<KeyPoint> keypoints;
	//detector->detect(denoise, keypoints);
	//
	//Mat src_with_keypoints;
	//
	//GaussianBlur(denoise, denoise, Size(7, 7), 1.5, 1.5);

	//drawKeypoints(denoise, keypoints, src_with_keypoints, Scalar(255, 0, 0),
	//	DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//resize(src_with_keypoints, src_with_keypoints, Size(555, 555), 0.25, 0.25, INTER_AREA);

	//imshow("Keypoints", src_with_keypoints);
	//
	//cout << "the size of keypoints vector is : " << keypoints.size();
	//waitKey(0);

	Mat src = imread("./ccm/coating/6_0_2.jpg", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image Load Failed" << endl;
	}

	// 노이즈 제거
	Mat denoise;
	fastNlMeansDenoising(src, denoise, 7.0, 7, 21);

	// Otsu 알고리즘 이용해 영상 이진화
	Mat dst;
	threshold(denoise, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// 크기 조절
	resize(dst, dst, Size(555, 555), 0.25, 0.25, INTER_AREA);

	//// 얼룩검출 객체 생성
	//Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();

	//// 키포인트 개수 변수 생성
	//vector<KeyPoint> keypoints;

	// 블러링
	Mat blur;
	GaussianBlur(dst, blur, Size(7, 7), 1.5, 1.5);

	//// 얼룩 검출 수행
	//detector->detect(blur, keypoints);

	//// 검출된 얼룩 그리기
	//drawKeypoints(blur, keypoints, blur, Scalar(255, 0, 0),
	//		DrawMatchesFlags::DRAW_OVER_OUTIMG);

	/*cout << "the size of keypoints vector is : " << keypoints.size();*/
	
	
	vector<Vec2f> lines;

	HoughLines(blur, lines, 1, CV_PI / 180, 150);
	
	Mat img_canny;
	Canny(blur, img_canny, 150, 255);

	Mat img_hough;
	blur.copyTo(img_hough);

	Mat img_lane;
	threshold(img_canny, img_lane, 150, 255, THRESH_MASK);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(blur, pt1, pt2, Scalar(0, 0, 255), 2, 8);
		line(blur, pt1, pt2, Scalar::all(255), 1, 8);
	}

	imshow("dst", img_hough);
	waitKey(0);
	
	return 0;

}