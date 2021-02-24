#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_threshold(int pos, void* userdata);

int main() {
	Mat src;

	src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 200, on_threshold, (void*)&src); // src�� �ּ� ������ �����ͷ� ����
	setTrackbarPos("Threshold", "dst", 11); // �ʱ⿡ Ʈ���� ��ġ 11�� ����

	waitKey();
	return 0;
}

void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata; // userdata�� mat*���� ����ȯ�� ���� ����

	int bsize = pos; // blocksize
	if (bsize % 2 == 0)bsize--; // blocksize�� Ȧ��
	if (bsize < 3) bsize = 3;

	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);
}
