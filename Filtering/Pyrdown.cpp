#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img = imread("Lenna.png"), img2;
	namedWindow("Example1", WINDOW_AUTOSIZE);
	namedWindow("Example2", WINDOW_AUTOSIZE);
	imshow("Example1", img);
	pyrDown(img, img2); // Blurs with Gaussian and downsize of image
	imshow("Example2", img2);
	waitKey(0);
	destroyWindow;
	return 0;
}