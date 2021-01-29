#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void MatOp1() {
	Mat img1; // empty Matrix

	Mat img2(480, 640, CV_8UC1); // unsigned char, 1-channel
	Mat img3(480, 640, CV_8UC3); // unsigned char, 3-channel
	Mat img4(Size(640, 480), CV_8UC3); // Size(width, height)

	Mat img5(480, 640, CV_8UC1, Scalar(128)); // intial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255)); // intial values, red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1); // 0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1); // 1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1); // identity matrix

	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({ 2,3 }, { 1,2,3,4,5,6 });

	mat4.create(256, 256, CV_8UC3); // unsigned char, 3-channel
	mat5.create(4, 4, CV_32FC1); // float 1-channel

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
}

void MatOp2() {
	Mat img1 = imread("lenna.jpg");

	Mat img2 = img1;
	Mat img3;
	img3 = img1;

	Mat img4 = img1.clone();
	Mat img5;
	img1.copyTo(img5);

	img1.setTo(Scalar(0, 255, 255)); // yellow

	waitKey();
	destroyAllWindows();
}