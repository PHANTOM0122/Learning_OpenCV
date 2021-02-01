#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_level_change(int pos, void* userdata);

int main(){

	Mat img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");
	createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img); // Userdata is img address!
	setTrackbarPos("level", "image", 200);
	namedWindow("img");  
	imshow("img", img);
	waitKey();

	return 0;
}

void on_level_change(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;

	img.setTo(pos * 16);
	imshow("image", img);
}
