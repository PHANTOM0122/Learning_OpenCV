#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void sobelEdge();
void canny_edge();

int main() {
	//sobelEdge();
	canny_edge();
}

void sobelEdge() {
	Mat src = imread("lenna256.bmp");
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag); // 벡터의 크기 계산
	fmag.convertTo(mag, CV_8UC1); 

	Mat edge = mag > 150; // gradient threshold 150으로 판별

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

void canny_edge() {
	Mat src = imread("lenna.bmp",IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}







