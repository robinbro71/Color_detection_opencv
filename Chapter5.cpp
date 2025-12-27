#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ///////////////////////  Warp Image ////////////////////////////////

float w = 250, h = 350;
Mat matrix, imgWrap;

void main() {
	
	std::string path = "Resources/cards.jpg";
	Mat img = imread(path);

	Point2f src[4] = { {60, 324}, {341, 277}, {87, 636}, {404, 573} };
	Point2f dst[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWrap, matrix, Point(w, h));

	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}


	imshow("image", img);
	imshow("image Warp", imgWrap);

	waitKey(0);

}





