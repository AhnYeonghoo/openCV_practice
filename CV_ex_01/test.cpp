#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main22()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Cant open the camera" << endl;
		return -1;
	}

	Mat img;
	
	
	while (1)
	{
		cap >> img;
		imshow("camera img", img);
		if (waitKey(1) == 27) break;
	} 

	return 0;
}
