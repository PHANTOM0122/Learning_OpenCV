컬러 영상 처리
=================
## 10-1) 컬러 영상 다루기
### 10-1-1) 컬러 영상의 픽셀 값 참조
* imread() 함수를 통해 컬러 영상 정보 얻음
* B,G,R 각 생상 성분 값은 uchar 자료형을 사용하여 표현
* **vec3b자료형을 이용하여 B,G,R 표현 / vec3b& pixel = img.at<vec3b>(0,0);**
* **vec3b class를 통해 B,G,R 값 표현 / uchar b1 = pixel[0](B), uchar b2 = pixel[1](G), uchar b3 = pixel[3](R)**
* pointer를 이용하여서도 표현 가능. 
<pre><code>
vec3b * ptr = img.ptr<vec3b>(0); // 0번째 시작 픽셀주소
uchar b2 = ptr[0][0] // (0,0)의 좌표 픽셀의 B
uchar g2 = ptr[0][1] // (0,0)의 좌표 픽셀의 G
uchar r2 = ptr[0][2] // (0,0)의 좌표 픽셀의 R 
</code></pre>
#### Example code) 컬러 영상의 픽셀값 반전
<pre><code>
void colorInverse() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type()); // 반전된 영상 저장할 dst영상

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			//invesere color
			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108613589-cfe6d680-7436-11eb-85d3-92e542d803b5.png)
### 10-1-2) 색 공간 변환
> **void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0;)**
* src: 입력영상
* dst: 결과영상
* code: 색 공간 변환 코드
* dstCn: 결과 영상의 채널 수
* ![image](https://user-images.githubusercontent.com/50229148/108624608-49a7b000-7489-11eb-9d5d-a9269d72442c.png)

#### BGR2GRAY 와 GRAY2BGR
* **BGR2GRAY는 영상의 메모리를 아껴서 연산 속도 향상 시킨다**
* **GRAY2BGR은 흑백영상을 컬러영상으로 변환**

#### BGR2HSV 와 HSV2BGR
* **HSV색 모델은 색상, 채도(색의 순도), 명도(빛의 세기)로 색을 표현하는 방식이다.**

#### BGR2YCrCb 와 YCrCb2BGR
* Y성분은 밝기와 휘도를 나타내고 Cr과 Cb 성분은 색상 또는 색차 정보를 나타난다.
<pre><code>
void colorGrayscale() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108625309-942b2b80-748d-11eb-8217-040a3e8003cd.png)
### 10-1-3) 색상 채널 나누기
#### split()함수를 통한 색상 채널 정보 나누기
**void split(const Mat& src, Mat* mvbegin)**
**void split(InputArray src, OutputArray mv);**
* src : 입력 다채널 행렬
* mvbegin : 분리된 1채널 행렬을 저장할 mat배열 주소
* mv: 분리된 1채널 행렬을 저장할 벡터
#### merge()함수를 통한 색상 채널 정보 통합
**void merge(const Mat* mv, size_t count, OutputArray dst);**
**void merge(InputArrayofArrays mv, OutputArray dst);**
* mv : 1채널 행렬을 저장하고 있는 배열 혹은 벡터. 모든 행렬은 크기와 길이가 같아야 한다
* count : Mat 배열의 크기
* dst : 출력 다채널 행렬
<pre><code>
void colorSplit() {
	Mat src = imread("candies.png");
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);
	imshow("G_plane", bgr_planes[1]);
	imshow("R_plane", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108625540-d43ede00-748e-11eb-815e-974b476ce63f.png)

## 10-2) 컬러 영상 처리 기법
### 10-2-1) 컬러 히스토그램 평활화
* **컬러 영상의 색감은 변경하지 않고, 명암비를 높이려면 영상의 밝기 정보만을 사용해야 한다. 입력 영상을 밝기 정보와 색상 정보로 분리한 이후, 밝기 정보에 대해서만 히스토그램 평활화를 수행한다**
![image](https://user-images.githubusercontent.com/50229148/108626011-59c38d80-7491-11eb-8e49-3d812969547b.png)
<pre><code>
int main(void)
{
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y channel

	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108625940-f0dc1580-7490-11eb-9230-176f3a5461d6.png)
### 10-2-2) 색상 범위 지정에 의한 영역 분할
* 특정 색상을 추출하는 작업이 많이 사용. 
* RGB 색 공간보다는 HSV등의 색상(H)정보가 따로 설정되어 있는 색 공간을 사용하는 것이 유리하다.
> **inRange()함수를 통한 특정 색상 추출**
  * 지정한 밝기 또는 색상 범위에 포함되어 있으면 흰색, 그렇지 않으면 검은색으로 채워진 마스크 영상 dst를 반환합니다.
![image](https://user-images.githubusercontent.com/50229148/108626660-afe60000-7494-11eb-8f89-7589aca42d55.png)

**void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst);**
* lowerb : 하한값. 주로 Mat or Schalar 객체 지정
* upperb : 상한값. 주로 Mat or Schalar 객체 지정
* dst : 출력 마스크 영상. 입력 영상과 크기가 같다, 타입은 CV_8UC1

#### Example code) 트랙바를 이용한 상한값, 하한값 설정
<pre><code>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int lower_hue = 49, upper_hue = 80;
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

int main(int argc, char* argv[])
{
	Mat src = imread("candies.png", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	cvtColor(src, src_hsv, COLOR_BGR2GRAY);

	imshow("src", src);

	namedWindow("mask");
	createTrackbar("Lower hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper hue", "mask", &upper_hue, 179, on_hue_changed);
	on_hue_changed(0, 0);

	waitKey();
	return 0;
}

void on_hue_changed(int, void*) {
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);
	inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108626612-5c73b200-7494-11eb-8827-69703b7dba77.png)
### 10-2-3) 히스토그램 역투영
* 사람의 피부색처럼 미세한 변화가 있거나 색상 값을 수치적으로 지정하기 어려운 경우에는 inRange()가 적합하지 않다
* **입력 영상서 찾고자 하는 객체의 기준 영상을 미리 가지고 있다면 컬러 히스토그램 정보를 이용하여 비슷한 색상 영역을 찾을 수 있다**
* **기준 영상으로부터 찾고자 하는 객체의 컬러 히스토그램을 미리 구하고, 주어진 영상에서 해당 히스토그램에 부합하는 영역을 찾아내는 기법**
> **calcBackProject()를 이용한 히스토그램 역투영**
**void calcBackProject(const Mat* images, int nimages, const int * channels, InputArray hist, OutputArray backProject, const float * * ranges, double scale = 1, bool uniform = true);** 
* images: 입력 영상의 배열 또는 입력 영상의 주소. 영상의 배열인 경우, 모든 영상의 크기와 깊이는 같아야 한다.
* nimages: 입력 영상의 갯수
* channels: 역투영 계산 시 사용할 채널 번호 배열
* hist: 입력 히스토그램
* backProject: 출력 히스토그램 역투영 영상. 입력 영상과 같은 크기, 같은 깊이를 갖는 1채널 행렬
* ranges: 각 차원의 히스토그램 빈 범위를 나타내는 배열의 배열
* scale: 히스토그램 역투영 값에 추가적으로 곱할 값
* uniform: 히스토그램 빈의 간격이 균등한지를 나타내는 플래그
**입력 영상 image에서 히스토그램 hist를 따르는 픽셀을 찾고, 그 정보를 backproject 영상으로 반환. **
#### Example code) 피부색 영역에 대한 히스토그램 추출, 입력 영상에서 피부색 영역을 검출
<pre><code>int main()
{
	// Calculate CrCb histogram from a reference image

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	// Apply histogram backprojection to an input image

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey(0);

	return 0;
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108627608-e4a88600-7499-11eb-9ccd-884ba33d65c7.png)
