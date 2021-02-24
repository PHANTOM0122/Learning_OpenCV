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
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // src의 주소 영상을 데이터로 전달
	setTrackbarPos("Threshold", "dst", 128); // 초기에 트랙바 위치 128로 설정후 한번 실행

	waitKey();
	return 0;
}

void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata; // userdata를 mat*으로 형변환후 변수 참조
	
	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); // trackbar pos값을 threshold로 갖는다

	imshow("dst", dst);
}
