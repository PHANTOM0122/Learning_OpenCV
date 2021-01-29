#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Vec3b p1, p2(0, 0, 255);
	p1.val[0] = 100;

	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;
}