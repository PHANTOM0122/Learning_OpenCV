#include "opencv2/highgui/highgui.hpp" //Include file for every supported OpenCV function

#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img = imread("Lenna.png"); // This line loads image "Lenna.png" 
	
	if (img.empty())
		return -1; // Checks to see if an image was in fact read 
	namedWindow("Example1", WINDOW_AUTOSIZE); // Opens a window on the screen that can contain and display an image.
											  // WINDOW_AUTOSIZE will expand or contract automatically , resized by the user.	
	imshow("Example1", img); // Display image
	waitKey(2000); // Asks the program to stop and wait for a keystroke
	destroyWindow("Example1"); // Close the window and deallocate any associated memory usage
	
}