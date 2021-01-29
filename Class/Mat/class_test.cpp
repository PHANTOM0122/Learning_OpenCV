#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int ac, char** av) {

	Point pt1;
	pt1.x = 5;
	pt1.y = 10;
	
	Size sz1;
	sz1.width = 5;
	sz1.height = 10;
	
	Rect r1(0, 0, 5, 10);

	Range r(0, 10);

	cout << pt1 << endl;
	cout << sz1 << endl;
	cout << r1 << endl;
	cout << r << endl;

	return 0;
}