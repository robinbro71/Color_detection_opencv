#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ///////////////////////  Basic Functions ////////////////////////////////

void main() {
	
	std::string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7,7), 5, 0);
	Canny(imgBlur, imgCanny, 50, 150);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));  
	dilate(imgCanny, imgDia, kernel);
	erode(imgDia, imgErode, kernel);

	imshow("image", img);
	imshow("image Gray", imgGray);
	imshow("image Blur", imgBlur);
	imshow("image edge", imgCanny);
	imshow("image Dialation", imgDia);
	imshow("image Erode", imgErode);
	waitKey(0);

}





