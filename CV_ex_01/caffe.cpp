#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main()
{
	string CLASSES[] = { "background", "aeroplane", "bicycle", "bird", "boat",
	"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
	"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
	"sofa", "train", "tvmonitor" };

	// �Է� �̹��� �ҷ�����
	Mat img = imread("bird.jpg");

	// ������ �� �ҷ�����
	Net net = readNetFromCaffe("MobileNetSSD_deploy.prototxt", "MobileNetSSD_deploy.caffemodel");

	// ��ü ���� ����
	Mat blob = blobFromImage(img, 0.007843, Size(300, 300), Scalar(127.5, 127.5, 127.5));
	net.setInput(blob);
	Mat detection = net.forward();

	// ����� ��ü ���� ���
	Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
	for (int i = 0; i < detectionMat.rows; i++)
	{
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > 0.4)
		{
			int class_id = (int)(detectionMat.at<float>(i, 1));
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * img.cols);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * img.rows);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * img.cols);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * img.rows);

			// ����� ��ü ��ġ ǥ��
			rectangle(img, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 2);

			// ����� ��ü �з� �� ��Ȯ�� ǥ��
			String label = format("%s: %.2f", CLASSES[class_id].c_str(), confidence);
			int baseline;
			Size label_size = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline);
			rectangle(img, Point(x1, y1 - label_size.height), Point(x1 + label_size.width, y1), Scalar(0, 255, 0), -1);
			putText(img, label, Point(x1, y1), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1);
		}
	}

	// ��� �̹��� ���
	imshow("result", img);
	waitKey(0);
	return 0;
	
}