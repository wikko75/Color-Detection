#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include<iostream>

using namespace cv;
using namespace std;

Mat imgHSV;
Mat mask;

int hMin = 0, sMin = 0, vMin = 0;
int hMax = 179, sMax =255, vMax = 255;

void createTrackBarsWindow(const string& WindowName, int flags, int* hMax,
	int* hMin, int* sMax, int* sMin, int* vMin, int* vMax);


int main()
{
	VideoCapture vc = VideoCapture(0);
	
	if (vc.isOpened() == false)
	{
		std::cerr << "Can not detect camera!/n";
		return 1;
	}
	
	createTrackBarsWindow("TrackBars", (640,200), &hMax, &hMin, &sMax, &sMin, &vMax, &vMin);
	
	Mat frame;
	
	while (true)
	{ 
		vc.read(frame);

		Scalar lower(hMin, sMin, vMin);
		Scalar upper(hMax, sMax, vMax);

		cvtColor(frame, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, lower, upper, mask);

		
		imshow("Camera View", frame);
		imshow("image hsv", imgHSV);
		imshow("image mask", mask);

		waitKey(1);
	}

	return 0;
}

void createTrackBarsWindow(const string &WindowName,int flags, int* hMax,
						   int* hMin, int* sMax, int* sMin, int* vMin, int* vMax)
{
	namedWindow(WindowName, flags);
	createTrackbar("HueMin", "TrackBars", hMin, 179);
	createTrackbar("HueMax", "TrackBars", hMax, 179);
	createTrackbar("SaturationMin", "TrackBars", sMin, 255);
	createTrackbar("SaturationMax", "TrackBars", sMax, 255);
	createTrackbar("ValueMin", "TrackBars", vMin, 255);
	createTrackbar("ValueMax", "TrackBars", vMax, 255);
}