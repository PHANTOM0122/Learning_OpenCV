#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	Mat img1 = imread("lenna.png",IMREAD_GRAYSCALE);
	if (img1.empty()) {
		cout << "unable to open" << endl;
		exit(1);
	}

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << "mat1:\n" << mat1 << endl;

	mat1.resize(6, 100);
	cout << "mat1:\n" << mat1 << endl;
}