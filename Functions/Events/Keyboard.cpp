#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("lenna.png");

	if (img.empty()) {
		cout << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("img");
	imshow("img", img);

	while (true) {
		int keycode = waitKey();

		if (keycode == 'i' || keycode == 'I') {
			img = ~img;
			imshow("img", img);
		}
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q') {
			break;
		}
	}
	return 0;
}