#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ///////////////////////  Color Detection ////////////////////////////////

Mat imgHsz, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

void main() {
	
	std::string path = "Resources/shapes.png";
	Mat img = imread(path);
	cvtColor(img, imgHsz, COLOR_BGR2HSV);

	namedWindow("TrackBars", (640, 200));
	createTrackbar("Hue Min", "TrackBars", &hmin, 179);
	createTrackbar("Hue Max", "TrackBars", &hmax, 179);
	createTrackbar("Sat Min", "TrackBars", &smin, 255);
	createTrackbar("Sat Max", "TrackBars", &smax, 255);
	createTrackbar("Val Min", "TrackBars", &vmin, 255);
	createTrackbar("Val Max", "TrackBars", &vmax, 255);

	while(true) {

		imshow("image", img);
		imshow("image HSV", imgHsz);
		imshow("image Mask", mask);
		waitKey(1);

	}

}