#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void labeling_basic();
void labelint_stats();

int main() {
	// labeling_basic();
	labelint_stats();
}

void labeling_basic() {
	uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	Mat src = Mat(8, 8, CV_8UC1, data) * 255;

	Mat labels;
	int cnt = connectedComponents(src, labels); // 객체의 갯수 + 1(배경)

	cout << "src: \n" << src << endl;
	cout << "dst: \n" << labels << endl;
	cout << "number of labels: " << cnt << endl;
}

void labelint_stats() {
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int i = 1; i < cnt; i++) { // 0은 배경이기 때문
		int* p = stats.ptr<int>(i); // stats 배열

		if (p[4] < 20) continue; // 객체의 픽셀 갯수(면적. 4번째 열)이 20이하면 잡음이라고 간주

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]),Scalar(0,255,255),2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}