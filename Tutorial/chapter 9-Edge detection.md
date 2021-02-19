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
