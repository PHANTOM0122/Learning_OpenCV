#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img1 = imread("lenna.png");
	if (img1.empty()) {
		cerr << "Unable to open\n";
		exit(1);
	}

	cout << "Width: " << img1.cols << endl;
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;


	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
} 