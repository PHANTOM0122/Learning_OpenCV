#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();

int main() {

	//camera_in();
	//video_in();
	camera_in_video_out();
	
}

void camera_in() {
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (1) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();
}

void video_in() {
	VideoCapture cap("stopwatch.avi");
	if(!cap.isOpened())
	{
		cout << "Video open failed!" << endl;
		return;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count : " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;
	
	double fps = cap.get(CAP_PROP_FPS); // Get video frames per sec!
	cout << "FPS: " << fps << endl;

	int delay = cvRound(1000 / fps); // Get delay value for waitKey() parameter

	Mat frame, inversed;
	while (1) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame; // inversed frames
		
		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
}

void camera_in_video_out()
{
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Camera open failed!" << endl;
		return;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	
	
	double fps = cap.get(CAP_PROP_FPS);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w,h));
	
	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}

	Mat frame, inversed;

	while (1) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		outputVideo << inversed;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
	

}
