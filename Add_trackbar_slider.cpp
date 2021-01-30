#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int g_slider_position = 0; // Global variable to keep the trackbar slider position state
// Start out in single step mode
int g_run = 1; // Displays new frames as long it is different from zero
int g_dontset = 0; // Update trackbar position according to location in the video
VideoCapture g_cap;

void onTrackbarSlide(int pos, void*) {
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos); // Set the read position in units of frames.
	if (!g_dontset)
		g_run = 1;
	g_dontset = 0;
}

int main(int argc, char** argv) {
	cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);
	g_cap.open("vtest.avi");
	// Determine the number of frames in the video and the widtth and height of the video images.
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT); 
	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << " frames of dimensions("
		<< tmpw << ", " << tmph << ")." << endl;

	// Create trackbar itself
	cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide);

	cv::Mat frame;
	while (1) {
		// Set the g_run so that the next trackbar callback will not put us into single step mod, and invoke the trackbar callback to update the position of the slider displayed to user.
		if (g_run != 0) { 
			g_cap >> frame; 
			if (!frame.data) break;// Check the data
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			cv::setTrackbarPos("Position", "Example2_4", current_pos); // Set the trackbar position
			cv::imshow("Example2_4", frame);
			g_run -= 1; 
		}
		char c = (char)cv::waitKey(10);
		if (c == 's') // single step
		{
			g_run = 1; cout << "Single step, run = " << g_run << endl;
		}
		if (c == 'r') // run mode
		{
			g_run = -1; cout << "Run mode, run = " << g_run << endl;
		}
		if (c == 27)
			break;
	}
	destroyAllWindows();
	return(0);
}
