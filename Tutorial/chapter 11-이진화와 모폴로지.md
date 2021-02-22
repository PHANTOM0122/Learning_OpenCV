이진화와 모폴로지
=====================
## 11.1 이진화(Binarization)
* grayscale 영상의 pixel값을 0 또는 255로 변환하는 기법이다
* **이진화는 객체 영역과 배경 영역을 구분하기 위한 용도로 널리 활용된다**

### 11.1-1) Threshold를 이용한 이진화
* **영상의 이진화는 각 픽셀을 두개의 부류로 나누는 작업이다**
* **pixel의 값이 임계값(threshold)보다 크면 255, 작으면 0으로 설정한다**

![image](https://user-images.githubusercontent.com/50229148/108731653-1be96680-7570-11eb-9bcd-193f1e126e4d.png)

> **threshold()함수를 이용한 이진화**
**double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type);**
* thresh : 임계값
* maxval : THRESH_BINARY THRESH_BINARY_INV 방법을 사용할 때 결과 영상의 최댓값
* type : 임계값 연산 방법. 열거형 상수를 지정.
* **반환값 : 사용된 임계값을 반환**

|ThresholdTypes|설명|
|-----|-----|
THRES_BINARY	| ![image](https://user-images.githubusercontent.com/50229148/108731980-78e51c80-7570-11eb-91c9-dd8920d5a5b8.png)
THRES_BINARY_INV	|![image](https://user-images.githubusercontent.com/50229148/108732032-84d0de80-7570-11eb-903d-915e53154f3b.png) 
THRES_TRUNC	| ![image](https://user-images.githubusercontent.com/50229148/108732036-87333880-7570-11eb-98d1-e8a9ff9594c7.png)
THRES_TOZERO | ![image](https://user-images.githubusercontent.com/50229148/108732050-8ac6bf80-7570-11eb-8cb8-7ef0b7b91b9c.png)
THRES_TOZERO_INV | ![image](https://user-images.githubusercontent.com/50229148/108732061-8dc1b000-7570-11eb-8326-726b0ff370c7.png) 
THRES_OTSU |오츠(Otsu) 알고리즘을 이용한 자동 임계값 결정
THRES_TRIANGLE |삼각(triangle) 알고리즘을 이용한 자동 임계값 결정
* **오츠 연산, triangle을 사용한 임계값 결정 방법은 CV_8UC1 탕비의 영상에만 적용할 수 있으며 | 연산자를 이용하여 기존의 5개 상수와 같이 사용된다**
<pre><code>
Mat src = imread("camera.bmp", IMREAD_GRAYSCALE);
Mat dst;
int th = (int)threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
</code></pre>
#### Example) Trackbar를 이용한 이진화 예제
<pre><code>
int main(int argc, char* argv[]) {
	Mat src;

	if (argc < 2)
		src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	else
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src); // src의 주소 영상을 데이터로 전달
	setTrackbarPos("Threshold", "dst", 128); // 초기에 트랙바 위치 128로 설정후 한번 실행

	waitKey();
	return 0;
}

void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata; // userdata를 mat*으로 형변환후 변수 참조
	
	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY); // trackbar pos값을 threshold로 갖는다

	imshow("dst", dst);
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108734830-32dd8800-7573-11eb-8e9f-94c3fd0867a0.png)

### 11.1-2) Adaptive Threshold를 이용한 이진화
* 일반적인 threshold()함수는 영상 전체 픽셀에 동일하게 적용 -> 화면 일부가 어두운 경우 결과가 이상해짐.
* **adaptive threshold를 이용하는 경우 각 픽셀마다 서로 다른 threshold를 사용하여 효과적**
* 정해진 크기의 사각형 블록을 정하고, 블록 내부의 픽셀 값 분포로부터 고유의 임계값 결정
* 
![image](https://user-images.githubusercontent.com/50229148/108737008-805af480-7575-11eb-9ffd-abfe52717400.png)

**void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, itn blockSize, double C)**
* maxValue : 이진화 결과 영상의 최댓값
* adaptiveMethod : 블록 평균 계산 방법의 지정. ADAPTIVE_THRESHOLD_MEAN_C OR ADAPTIVE_THRESHOLD_GUASSIAN_C중 하나를 지정
* thresholdType : THRESH_BINARY OR THRESH_BINARY_INV중 하나 지정
* **blocksize: threshold계산시 사용하는 블럭 크기. 3보다 같거나 큰 홀수를 지정해야 한다**
* C : 임계값 조정을 위한 상수. 블록 평균에서 C를 뺀 값을 임계값으로 사용
- ADAPTIVE_THRESHOLD_MEAN_C -> 주변 영역의 픽셀로부터 산술 평균을 구한다
- ADAPTIVE_THRESHOLD_GUASSIAN_C -> 가우시안 마스크를 적용하여 가중 평균을 구한다.

#### Example) Trackbar를 이용한 이진화 예제2
<pre><code>
void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata; // userdata를 mat*으로 형변환후 변수 참조

	int bsize = pos; // blocksize
	if (bsize % 2 == 0)bsize--; // blocksize는 홀수
	if (bsize < 3) bsize = 3;

	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108737200-b7310a80-7575-11eb-8a89-1308cb2930a4.png)
## 11.2 Morphology 연산
* **Morphology 연산은 영상 내부 객체의 형태와 구조를 분석하고 처리하는 기법이다**
* 주로 이진화된 영상에서 객체의 모양을 변형하는 용도로 사용
###  11.2-1) 이진 영상의 침식과 팽창
* **모폴로지 연산을 정의하려면 먼저 구조 요소(연산의 동작을 결정하는 작은 크기의 행렬)를 정의해야 한다**
* 대부분의 경우 구조 요소의 중심을 고정점으로 사용
> **getStructuringElement()함수를 이용한 구조 요소 행렬 구하기**
**Mat getStructuringElement(int shape, Size ksize, Pointer anchor = Pointer(-1,-1));**
* shape : 구조 요소의 모양 (아래 표 참조)
* ksize : 구조 요소의 크기
* anchor : 구조 요소 중심 좌표. (-1,-1)을 지정하면 중앙을 중심 좌표로 사용
* 반환값 : 구조 요소 행렬
Morphshape|설명|
|-----|-----|
MORPH_RECT| 사각형 모양의 구조 요소
MORPH_CROSS| 십자가 모양의 구조 요소
MORPH_ELLIPSE| 타원 모양의 구조 요소. 사각형에 내접하는 타원 이용. 

![image](https://user-images.githubusercontent.com/50229148/108739390-f2343d80-7577-11eb-95fd-1c62dbfa3a9b.png)

> **erode()함수를 이용한 침식 연산**
**void erode(src, dst, InputArray kernel, Point anchor = point(-1,-1) int iterations = -1, int borderType = BOADER_CONSTANT, const Schalar& borderValue = morphologyDefaultBoarderValue());**
* kernel : 구조 요소. Mat을 지정하면 3x3 사각형 구조 요소 사용. 그 외는 getStructuingElement() 사용
* iteration : 반복 횟수
* boarderType : 가장자리 픽셀 확장 방식
* boarderValue : borderType이 BORDER_CONSTANT인 경우 확장된 가장자리 픽셀을 채울 값.

> **dilate()함수를 이용한 팽창 연산**
**void erode(src, dst, InputArray kernel, Point anchor = point(-1,-1) int iterations = -1, int borderType = BOADER_CONSTANT, const Schalar& borderValue = morphologyDefaultBoarderValue());**
* kernel : 구조 요소. Mat을 지정하면 3x3 사각형 구조 요소 사용. 그 외는 getStructuingElement() 사용
* iteration : 반복 횟수
* boarderType : 가장자리 픽셀 확장 방식
* boarderValue : borderType이 BORDER_CONSTANT인 경우 확장된 가장자리 픽셀을 채울 값.
#### Example 
<pre><code>
void erode_dilate()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}</code></pre>
* erode 영상은 객체 외관이 작아졌고 우측 하단 흰색 픽셀이 사라짐
* dilate 영상은 객체 외관이 확대되었고 객체 내부의 검은색 구멍은 좁아짐
![image](https://user-images.githubusercontent.com/50229148/108740392-f745bc80-7578-11eb-9ef9-72acb5fef8da.png)
