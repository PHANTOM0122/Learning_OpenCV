#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	Mat img1 = imread("cat.bmp");
	if (img1.empty()) {
		cerr << "Image load failed" << endl;
		exit(1);
	}

	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();
	Mat img4 = (img1.rowRange(180, 300)).colRange(200, 400);
	img2 = ~img2; // ¹ÝÀü

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);

	waitKey();
	destroyAllWindows();

}