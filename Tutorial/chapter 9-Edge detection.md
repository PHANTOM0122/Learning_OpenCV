Edge detection
================
## 9.1) Edge detection
### 9.1-1) 미분과 그래디언트
* **2차원 영상에서 Edge를 찾는 기본적인 방법은 그래디언트 크기가 특정 값보다 큰 위치를 찾는 것이다**
* **Edge 여부를 판단하기 위해 기준이 되는 값을 threshold라 하며, 이 값은 영상의 특성에 따라 다르며, 사용자의 경험에 의해 결정**
* **임계값이 높으면 밝기 차이가 급격한 edge만 검출되며, 낮으면 약한 edge도 검출된다**
### 9.1-2) 마스크 기반 에지 검출
* **잡음의 영향을 줄일 수 있도록 여러가지 방법의 미분 근사 마스크를 사용**
> **sobel(),Scharr() 함수를 이용한 편미분(소벨, 샤르 필터 마스크)**
**void Sobel(InputArray src, OutputArray dst, int depth, int dx, int dy, int ksize=3, double scale=1, double delta = 0, int boarderType = BOARDER_DEFAULT)**
**void Scharr(InputArray src, OutputArray dst, int depth, int dx, int dy, int ksize=3, double scale=1, double delta = 0, int boarderType = BOARDER_DEFAULT)**
* src: 입력 영상
* dst: 출력 영상. src와 같은 크기, 채널 수를 갖는다
* ddepth: 출력 영상의 깊이
* dx: x방향 미분 차수
* dy: y방향 미분 차수
* ksize: 소벨 커널의 크기
* scale: 필터링 연산 후 추가적으로 곱할 값
* delta: 필터링 연산 후 추가적으로 더할 값
* boarderType: 가장자리 픽셀 확장 방식
<pre><code>
void sobelEdge() {
	Mat src = imread("lenna256.bmp");
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	magnitude(dx, dy, fmag); // 벡터의 크기 계산
	fmag.convertTo(mag, CV_8UC1); 

	Mat edge = mag > 150; // gradient threshold 150으로 판별

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}
</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108449733-4f45a000-72a7-11eb-9942-0216a2343f4b.png)
### 9.1-3) Canny-edge-detection
> #### canny edge 수행 과정
1) 가우시안 필터링 
* **영상에 포함된 잡음을 제거하기 위함. 적절한 표준 편차를 선택하여야 smoothing시 edge의 세기 감소 방지가능**\
2) 그래디언트 계산
3) 비최대 억제
* **Edge가 두껍게 표현되는 것을 방지. 이것을 통해 가장 큰 위치의 픽셀만 에지로 판별**
4) 이중 임계값을 이용한 히스테리시스 에지 트래킹
* **2개의 임계값을 사용하여 strong edge, weak edge, not edge 구분. 이후 hystreisis판별을 통해 strong과 연결된 weak는 edge로, 연결되지 않은 weak는 not edge로 판별**
> #### Canny()를 이용한 edge detection
**void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize =3, bool L2gradient = false)**
**void Canny(InputArray dx, InputArray dy, OutputArray edges, double threshold1, double threshold2, bool L2gradient)**
* image: 8비트 입력 영상
* dx: 입력영상의 x방향 미분 영상. cv_16sc1 or cv_16sc3
* dy: 입력영상의 y방향 미분 영상. cv_16sc1 or cv_16sc3
* edges: 출력 에지 영상. 입력 영상과 크기가 같은 8비트 단일 채널 영상
* threshold1: hystreisis 에지 검출을 위한 임계값 1. 보통 낮은 임계값 지정
* threshold2: hystreisis 에지 검출을 위한 임계값 2. 보통 높은 임계값 지정
* appertureSize: gradient 계산을 위한 소벨 마스크 크기
* L2gradient: 그래디언트 크기 계산 시 L2 노름을 사용하려면 true 지정. 이 값이 false이면 L1노름을 사용
<pre><code>
void canny_edge() {
	Mat src = imread("lenna.bmp",IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108452755-65a22a80-72ac-11eb-98c5-46f92e817dc1.png)

