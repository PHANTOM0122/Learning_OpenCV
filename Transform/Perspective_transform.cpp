#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src;
Point2f srcQuad[4], dstQuad[4];

void on_mouse(int event, int x, int y, int flags, void* userdata);

int main() {
	src = imread("card.bmp");
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();
	
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void* userdata) {

	static int cnt = 0;
	if (event == EVENT_LBUTTONDOWN) { // 마우스 왼쪽 버튼을 클릭할 때만 처리
		if (cnt < 4) {
			srcQuad[cnt++] = Point2f(x, y); // left마우스 클릭 지점 좌표 저장

			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1); // x,y 중심으로 반지름 5 빨간원 표시
			imshow("src", src);

			if (cnt == 4) {
				int w = 200, h = 300;
				dstQuad[0] = Point2f(0, 0);
				dstQuad[1] = Point2f(w-1, 0);
				dstQuad[2] = Point2f(w-1, h-1);
				dstQuad[3] = Point2f(0, h-1);

				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h));
				imshow("dst", dst);
			}
		}
	}
}