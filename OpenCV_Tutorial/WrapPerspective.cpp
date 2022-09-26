#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include<iostream>

using namespace cv;
using namespace std;

float width = 250;
float height = 350;

Mat matrix;
Mat imgWarp;

void main()
{
	// importing images
	string path = "Resources/cards.jpg";
	Mat img = imread(path);
	
	Point2f src[4] = { {531,144}, {406,395}, {769, 192}, {675, 455}};
	Point2f dst[4] = { {0.0f, 0.0f}, {0.0f, height}, {width, 0.0f}, {width, height} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(width, height));


	for (int i = 0; i < 4; i++)
	{
		circle(img, Point(src[i]), 10, Scalar(0, 0, 0), 2);
	}
	imshow("Image", img);
	imshow("Warp Perspective", imgWarp);
	waitKey(0);
	
}

