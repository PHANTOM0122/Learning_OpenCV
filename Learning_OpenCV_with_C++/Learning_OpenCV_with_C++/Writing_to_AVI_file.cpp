#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	namedWindow("Example2_10", WINDOW_AUTOSIZE);
	namedWindow("Log_Polar", WINDOW_AUTOSIZE);

	VideoCapture capture;
	
	double fps = capture.get(CAP_PROP_POS_FRAMES);
	Size size(
		(int)capture.get(CAP_PROP_FRAME_WIDTH),
		(int)capture.get(CAP_PROP_FRAME_HEIGHT)
	);

	VideoWriter writer;
	writer.open(argv[2], CV_FOURCC('M', 'J', 'P', 'G'), fps, size);

	Mat logpolar_frame(size, CV::U8C3), bgr_frame;
	for (;;) {
		capture >> bgr_frame;
		if (bgr_frame.empty())
			break; // End if done
		imshow("Example2_10", bgr_frame);
		logPolar(
			bgr_frame, // Input color frame
			logpolar_frame, // Output log-polar frame
			Point2f( //Centerpoint for log-polar transformaiton
				bgr_frame.cols / 2, // x
				bgr_frame.rows / 2 //y
			),
			40, // Magnitude(scale parameter)
			WARP_FILL_OUTLIERS); // Fill outliers with zero
		
		imshow("Log_Polar", logpolar_frame);
		writer << logpolar_frame;
		if (waitKey(10) == 27) break;
	}
	capture.release();
}