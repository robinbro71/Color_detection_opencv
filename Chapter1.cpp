#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ///////////////////////  images ////////////////////////////////

//void main() {
//	
//	std::string path = "Resources/test.png";
//	Mat img = imread(path);
//	imshow("image", img);
//	waitKey(0);
//
//}

/// ///////////////////////  video ///////////////////////////////

//void main() {
//
//	std::string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//
//	while (true) {
//
//		cap.read(img);
//
//		imshow("image", img);
//		waitKey(100);
//
//	}
//
//}

/// ///////////////////////  webcam ///////////////////////////////

void main() {

	VideoCapture cap(0);
	Mat img;


	while (true) {

		cap.read(img);

		imshow("image", img);
		waitKey(1);

	}

}



