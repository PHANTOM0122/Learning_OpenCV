#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	namedWindow("Example2", WINDOW_AUTOSIZE);
	VideoCapture cap; 
	cap.open("vtest.avi"); // Open a video file "vtest.avi"
	Mat frame;
	while (true) {
		cap >> frame; 
		if (!frame.data) break; // Ran out of film
		imshow("Example2", frame); // Display a video
		if (waitKey(33) >= 0) break;

	}
	return 0;
}