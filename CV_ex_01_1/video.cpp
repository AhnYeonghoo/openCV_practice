#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int mainvideo()
{
	VideoCapture cap(0);
	
	if (!cap.isOpened())
	{
		cerr << "Camera open failed!" << endl;
		return -1;
	}
	
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	
	Mat frame, inversed;
	
	while (true)
	{
		cap >> frame;
		if (frame.empty())
			break;
		
		inversed = ~frame;
		
		imshow("frame", frame);
		imshow("inversed", inversed);
		
		if (waitKey(10) == 27) break;

	}
	destroyAllWindows();
	return 0;
}

