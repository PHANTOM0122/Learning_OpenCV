#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void noise_gaussian();
void filter_bilateral();
void filter_median();

int main(){
	//noise_gaussian();
	//filter_bilateral();
	filter_median();
}

void noise_gaussian() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void filter_bilateral() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	imshow("GaussianBlur", dst1);
	imshow("bilateralFilter", dst2);

	waitKey();
	destroyAllWindows();
}

void filter_median() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255; // src 영상에서 10%에 해당하는 픽셀 값을 0또는 255로 설정합니다
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("GaussianBlur", dst1);
	imshow("medianFilter", dst2);

	waitKey();
	destroyAllWindows();
}