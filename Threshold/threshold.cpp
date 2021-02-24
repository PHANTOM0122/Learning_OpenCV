#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_threshold(int pos, void* userdata);

int main(int argc, char* argv[]) {
	Mat src;

	if (argc < 2)
		src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	else
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // src�� �ּ� ������ �����ͷ� ����
	setTrackbarPos("Threshold", "dst", 128); // �ʱ⿡ Ʈ���� ��ġ 128�� ������ �ѹ� ����

	waitKey();
	return 0;
}

void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata; // userdata�� mat*���� ����ȯ�� ���� ����
	
	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); // trackbar pos���� threshold�� ���´�

	imshow("dst", dst);
}
