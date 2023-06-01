#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int mainvideo2()
{
	VideoCapture cap("stopwatch.avi");
	
	if (!cap.isOpened())
	{
		cerr << "Video open failed!" << endl;
		return -1;
	}
	
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;
	
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	
	int delay = cvRound(1000 / fps);
	
	Mat frame, inversed;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
		
		inversed = ~frame;
		
		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
		{
			break;
		}
	}

	destroyAllWindows();

	return 0;
}

