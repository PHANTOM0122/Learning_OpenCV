#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


int main() {
	Scalar gray = 128; // brightness
	cout << "gray: " << gray << endl;

	Scalar yellow(0, 255, 255); // B G R 
	cout << "yellow: " << yellow << endl;

	Mat img1(256, 256, CV_8UC3, yellow);

	for (int i = 0; i < 4; i++)
		cout << yellow[i] << ' '; // B G R transperentness
}