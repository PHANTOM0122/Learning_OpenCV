#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Create window
	namedWindow("Cam", WINDOW_AUTOSIZE);
	namedWindow("CannyCam", WINDOW_AUTOSIZE);
	
	VideoCapture cap;
	
	// Open defualt camera
	if(argc ==1)
		cap.open(0);

	// Check camera opened
	if (!cap.isOpened()) {
		cerr << "Could not caputured! " << endl;
		return -1;
	}

	Mat frame;
	Mat img_gry, img_cny;

	while (true) {
		cap >> frame;
		if (!frame.data) // Check whether data is empty!
			break;

		// Gaussianblur 
		GaussianBlur(frame, frame, Size(7, 7), 3, 3);
		imshow("Cam", frame);

		cvtColor(frame, img_gry, COLOR_BGR2GRAY);

		// Canny edge method
		Canny(img_gry, img_cny, 10, 100, 3, true);

		imshow("CannyCam", img_cny);

		// 'ESC' to quit
		if (waitKey(1) == 27) break;
	}
	destroyWindow;
}

//GaussianBlur(image, out, Size(5, 5), 3, 3); 