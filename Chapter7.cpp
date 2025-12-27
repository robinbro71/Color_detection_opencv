#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ///////////////////////  Shape Detection ////////////////////////////////

Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;
void getCountours(Mat imgDia, Mat img) {

	std::vector<std::vector<Point>> countours;
	std::vector<Vec4i> hierarcy;

	findContours(imgDia, countours, hierarcy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, countours, -1, Scalar(255, 0, 255), 2);

	for (int i = 0; i < countours.size(); i++) {
		
		int area = contourArea(countours[i]);
		std::cout << area << std::endl;

		std::vector<std::vector<Point>> conPoly(countours.size());
		std::vector<Rect> boundRect(countours.size());
		String objType;

		if (area > 1000) {
		
			float peri = arcLength(countours[i], true);
			approxPolyDP(countours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			std::cout << conPoly[i].size() << std::endl;
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			int objcor = (int)conPoly[i].size();

			if (objcor == 3) { objType = "Triangle"; }
			else if (objcor == 4) {
				
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio >= 0.95 && aspRatio <= 1.05) { objType = "Square"; }
				else { objType = "Rectangle"; }
				std::cout << aspRatio << std::endl;
					
				}
			else if (objcor > 5) { objType = "Circle"; }

			putText(img, objType, { boundRect[i].x, boundRect[i].y-5 }, FONT_HERSHEY_DUPLEX, 0.5, Scalar(200, 100, 0), 2);
			
		
		}

	}

}

void main() {
	
	std::string path = "Resources/shapes.png";
	Mat img = imread(path);

	//Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDia, kernel);

	getCountours(imgDia, img);

	imshow("image", img);
//	imshow("image Gray", imgGray);
//	imshow("image Blur", imgBlur);
//	imshow("image Canny", imgCanny);
//	imshow("image Dialation", imgDia);
	waitKey(0);

}