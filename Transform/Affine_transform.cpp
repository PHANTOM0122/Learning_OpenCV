#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void affine_transform();
void affine_translation();
void affine_shear();
void affine_scale();
void affine_rotation();
void affine_filp();

int main() {
	//affine_transform();
	//affine_translation();
	//affine_shear();
	//affine_scale();
	//affine_rotation();
	affine_filp();

}

void affine_transform()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0); // 영상 좌측 상단
	srcPts[1] = Point2f(src.cols - 1, 0); // 영상 우측 상단
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1); // 영상 우측 하단

	// dst 영상은 평행사변형
	dstPts[0] = Point2f(50, 50); // 출력 영상 좌측 상단
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows-50);

	// Get Affine matrix
	Mat M = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_translation()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// 가로로 150 pix, 세로로 100 pix 만큼 이동 
	Mat M = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 });

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_shear()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	double mx = 0.3;
	// y좌표가 증가함에 따라 0.3y에 해당하는 x좌표에서 원본 영상 픽셀이 나타남
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 });

	Mat dst;
	// 전단 변환에 의해 짤리지 않도록 가로 크기를 cvRound 이용하여 조절
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void affine_scale()
{
	Mat src = imread("rose.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST); // x,y 비율 4배 확대
	resize(src, dst2, Size(1920, 1280)); // Size()를 이용한 4배 확대
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC); // 3차 보간법
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4); // 란초스 보간법


	imshow("src", src);
	imshow("dst1", dst1(Rect(400,500,400,400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));

	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}

void affine_rotation() {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	Mat M = getRotationMatrix2D(cp, 20, 1); // Rotate 20 degree. same Size!

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
void affine_filp() {
	Mat src = imread("eastsea.bmp");
	
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	int flipcode[] = { -1,0,1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipcode[i]);

		String desc = format("flipcode: %d", flipcode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255,0,0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}