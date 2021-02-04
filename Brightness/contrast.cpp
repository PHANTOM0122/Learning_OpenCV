#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void contrast1();
void contrast2();

int main() {
	//contrast1();
	contrast2();
}

void contrast1() {
	Mat src = imread("lenna.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	float s = 2.f;
	Mat dst = s * src; // �˾Ƽ� satured ������� ���ش�!

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void contrast2() {
	Mat src = imread("lenna.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha; // 128���� ũ�� �� ũ�� 128���� ������ �� �۰� �����
	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}