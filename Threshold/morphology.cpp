#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void erode_dilate();
void open_close();

int main() {
	//erode_dilate();
	open_close();
}

void erode_dilate() {
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU); // OTSU �̿��� �ڵ����� threshold

	Mat dst1, dst2;
	erode(bin, dst1, Mat()); // ħ��
	dilate(bin, dst2, Mat()); // ��â

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}
void open_close() {
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat dst1, dst2;
	morphologyEx(src, dst1, MORPH_OPEN, Mat());
	morphologyEx(src, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}