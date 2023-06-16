#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <time.h>
using namespace cv;
using namespace std;

int mainvectorreserve()
{
	vector<double> v1, v2;
	v1.reserve(10000000);
	
	double start_time = clock();
	for (int i = 0; i < v1.capacity(); i++)
	{
		v1.push_back(i);
	}

	printf("reserve() 사용 %5.2f ms\n", (clock() - start_time));
	
	start_time = clock();
	for (int i = 0; i < v1.capacity(); i++)
	{
		v2.push_back(i);
	}
	
	printf("reverse() 미사용 %5.2f ms\n", (clock() - start_time));
	return 0;
}