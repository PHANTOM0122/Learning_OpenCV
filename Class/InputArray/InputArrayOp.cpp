#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void PrintMat(InputArray _mat) {
	Mat mat = _mat.getMat();
	cout << mat << endl;
}

void InputArrayOp() {
	uchar data1[] = { 1,2,3,4,5,6 };
	Mat mat1(2, 3, CV_8U, data1);
	PrintMat(mat1);

	vector<float> vec1 = { 1.2f,3.4f,-2.1f };
	PrintMat(vec1);
}



int main() {
	InputArrayOp();
}