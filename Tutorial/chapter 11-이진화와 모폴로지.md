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
**void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, itn blockSize, double C)**
* maxValue : 이진화 결과 영상의 최댓값
* adaptiveMethod : 블록 평균 계산 방법의 지정. ADAPTIVE_THRESHOLD_MEAN_C OR ADAPTIVE_THRESHOLD_GUASSIAN_C중 하나를 지정
* thresholdType : THRESH_BINARY OR THRESH_BINARY_INV중 하나 지정
* **blocksize: threshold계산시 사용하는 블럭 크기. 3보다 같거나 큰 홀수를 지정해야 한다**
* C : 임계값 조정을 위한 상수. 블록 평균에서 C를 뺀 값을 임계값으로 사용
- ADAPTIVE_THRESHOLD_MEAN_C -> 주변 영역의 픽셀로부터 산술 평균을 구한다
- ADAPTIVE_THRESHOLD_GUASSIAN_C -> 가우시안 마스크를 적용하여 가중 평균을 구한다.

#### Example) Trackbar를 이용한 이진화 예제2
