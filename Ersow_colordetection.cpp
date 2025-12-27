#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;

/// ///////////////////////  webcam ///////////////////////////////
Mat imgHsz, mask;
int hmin = 147, smin = 78, vmin = 95;
int hmax = 166, smax = 175, vmax = 135;

int indexOfMax(const std::vector<int>& a) {
	if (a.empty())
		return -1;   // or throw, depending on what you prefer

	int maxIndex = 0;

	for (int i = 1; i < a.size(); i++) {
		if (a[i] > a[maxIndex]) {
			maxIndex = i;
		}
	}
	return maxIndex;
}

void getCountours(Mat mask, Mat img) {

	std::vector<std::vector<Point>> countours;
	std::vector<Vec4i> hierarcy;
	findContours(mask, countours, hierarcy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, countours, -1, Scalar(255, 0, 255), 3);

	std::vector<int> area_(countours.size());
	std::vector<std::vector<Point>> conPoly(countours.size());
	std::vector<Rect> boundRect(countours.size());
	for (int i = 0; i < countours.size(); i++) {
		int area = contourArea(countours[i]);
		area_[i] = contourArea(countours[i]);
		std::cout << area << std::endl;

		//if (area_[i] > 20) { //temp for largest contour
		//	float peri = arcLength(countours[i], true);
		//	approxPolyDP(countours[i], conPoly[i], 0.02 * peri, true);
		//	drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
		//	std::cout << conPoly[i].size() << std::endl;
		//	boundRect[i] = boundingRect(conPoly[i]);

		//	Point centerBox((boundRect[i].tl().x + boundRect[i].br().x) / 2, (boundRect[i].tl().y + boundRect[i].br().y) / 2);
		//	Point BTFrame(320, 480);

		//	rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		//	circle(img, centerBox, 3, Scalar(0, 255, 0), FILLED);
		//	line(img, centerBox, BTFrame, Scalar(0, 255, 0));
		//
		//}
	}
	if (area_.empty()) { return; }
	int i = indexOfMax(area_);

	if (area_[i] > 20) { //temp for largest contour
			float peri = arcLength(countours[i], true);
			approxPolyDP(countours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			std::cout << conPoly[i].size() << std::endl;
			boundRect[i] = boundingRect(conPoly[i]);

			Point centerBox((boundRect[i].tl().x + boundRect[i].br().x) / 2, (boundRect[i].tl().y + boundRect[i].br().y) / 2);
			Point BTFrame(320, 480);

			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			circle(img, centerBox, 3, Scalar(0, 255, 0), FILLED);
			line(img, centerBox, BTFrame, Scalar(0, 255, 0));
		
	}

}


void main() {

	VideoCapture cap(0);
	Mat img;

	namedWindow("TrackBars", (640, 200));
	createTrackbar("Hue Min", "TrackBars", &hmin, 179);
	createTrackbar("Hue Max", "TrackBars", &hmax, 179);
	createTrackbar("Sat Min", "TrackBars", &smin, 255);
	createTrackbar("Sat Max", "TrackBars", &smax, 255);
	createTrackbar("Val Min", "TrackBars", &vmin, 255);
	createTrackbar("Val Max", "TrackBars", &vmax, 255);


	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		cap.read(img);
		cvtColor(img, imgHsz, COLOR_BGR2HSV);
		inRange(imgHsz, lower, upper, mask);

		getCountours(mask, img);

		imshow("image", img);
		imshow("image HSV", imgHsz);
		imshow("image Mask", mask);

		waitKey(1);

	}

}