#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat img_rgb = imread("Lenna.png");
	Mat img_gry, img_cny;

	cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
	
	namedWindow("Example Gray", WINDOW_AUTOSIZE);
	namedWindow("Example Canny", WINDOW_AUTOSIZE);

	imshow("Example Gray", img_gry);

	Canny(img_gry, img_cny, 10, 100, 3, true); // Find edges using Canny algorithms
	imshow("Exmaple Canny", img_cny);


	waitKey(0);
}

