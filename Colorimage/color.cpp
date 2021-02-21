#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void colorInverse();
void colorGrayscale();
void colorSplit();

int main() {
	//colorInverse();
	//colorGrayscale();
	colorSplit();
}

void colorInverse() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type()); // 반전된 영상 저장할 dst영상

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			//invesere color
			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void colorGrayscale() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void colorSplit() {
	Mat src = imread("candies.png");
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}