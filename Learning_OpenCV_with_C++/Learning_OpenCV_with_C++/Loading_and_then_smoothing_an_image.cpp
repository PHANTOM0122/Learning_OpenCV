#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void example2_5(Mat& image) {
	// Create some windows to show the input and output images in
	namedWindow("Example2_5_in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5_out", WINDOW_AUTOSIZE);

	// Create a window to show our input image
	imshow("Example2_5_in",image);

	// Create an image to hold the smoothed output
	Mat out;

	// Do something with GaussianBlur(), blur(), medianBlur() or bilateralFilter()
	GaussianBlur(image, out, Size(5, 5), 3, 3); // Reduces image noises and reduce detailt to enhance image structures at different scales
	GaussianBlur(out, out, Size(5, 5), 3, 3);

	// Show the sommted image in the output window
	imshow("Example2_5_out", out);

	//Wait for the user to hit a key, windows will self destruct
	waitKey(0);

}

int main(int argc, char** argv) {

}

/*namedWindow("Example2", WINDOW_AUTOSIZE);
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
}*/