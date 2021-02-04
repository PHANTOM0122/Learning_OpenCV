#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void brightness1();
void brightness2();
void brightness3();
void brightness3_1();
void brightness4();
void on_brightness(int pos, void* userdata);

int main(){
	//brightness1();
	//brightness2();
	//brightness3();
	brightness4();
}

void brightness1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dst = src + 100; // or src += 100;
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void brightness2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++)
		for (int i = 0; i < src.cols; i++)
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void brightness3() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			int v = src.at<uchar>(j, i) + 100;
			dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v; // ��ȭ ������ ���. V>255�̸� 255, �ƴϸ� v. v<0�̸� 0 �ƴϸ� v����
		}
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void brightness3_1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness4() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*) & src); // ���α׷� ���� �� dstâ�� ���� ������ ���������� ǥ�õǵ��� ������ on_brightness()�Լ� ȣ��!
	on_brightness(0, (void*)&src);
	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}