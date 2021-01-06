#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv) { // argc: ������ ���� ����  argv: ���ڿ��� �Է¹޾Ƽ� �ش� ��ɾ� ����
	
	namedWindow("Exmaple", WINDOW_AUTOSIZE);
	VideoCapture cap;
	if (argc == 1)
		cap.open(0);// Open the default camera
	else
		cap.open("Lenna.png");

	if (!cap.isOpened()) { // Check if we succeeded
		cerr << "couldn't open capture. " << endl;
		return -1;
	}
	Mat frame;
	while (true) {
		cap >> frame;
		if (!frame.data)
			break;
		imshow("Example", frame);
		if (waitKey(10)==27) break;// Press ESC to quit
	}
	destroyWindow;
}