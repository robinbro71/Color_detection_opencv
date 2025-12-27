#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ///////////////////////  Resize and Crop ////////////////////////////////

void main() {
	
	std::string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResized,ingCrop;

	//std::cout << img.size() << std::endl;
	resize(img, imgResized, Size(), 0.2, 0.2);

	Rect roi(100, 100, 300, 250);
	ingCrop = img(roi);

	imshow("image", img);
	imshow("image Resized", imgResized);
	imshow("image Croped", ingCrop);

	waitKey(0);

}





