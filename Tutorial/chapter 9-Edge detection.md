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
## 9.2) 직선 검출과 원 검출
### 9.2-1) 허프 변환 직선 검출
>**HoughLines() 함수를 이용한 허프 변환 직선 검출 수행**
**void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0. double stn=0, double min_theth = 0, double max_theta = 0)**
* image: 8비트 단일 채널 입력 영상. 주로 에지 영상을 지정
* lines: 직선 정보(rho,theta)를 저장할 출력 벡터
* rho: 축적 배열에서 픽셀 단위
* theta: 축적 배열에서 라디안 단위
* threshold: 축적 배열에서 직선으로 판단할 임계값
* srn: 멀티 스케일 허프 변환에서 rho 해상도를 나누는 값. 양수를 지정시 rho/srn 해상도를 이용하여 멀티스케일 허프변환 수행
* stn: 멀티스케일 허프 변환에서 theta해상도를 나누는 값
* min_theta: 검출할 직선의 최소 theta 값
* max_theta: 검출할 직선의 최대 theta 
#### 직선 파라미터 정보를 이용하여 영상 위에 빨간색 직선을 그리는 예제
<pre><code>
void houghlines() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR); // 3채널 컬려 영상으로 변환

	// 반환하는 직선 정보를 이용하여 영상 위에 빨간색 직선을 그려 화면에 나타낸다
	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t; // x0, y0는 원점에서 직선에 수선을 내렸을 때 만나는 점. 
		double alpha = 1000; // alpha 값이 충분히 커야 pt1, pt2가 영상의 밖에 존재

		// pt1. pt2는 직선 영상을 그리기 위한 좌표
		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));

		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108454795-676ded00-72b0-11eb-9a33-b0416999d01e.png)
### 9.2-2) 확률적 허프 변환
>**HoughLinesP() 함수를 이용한 허프 변환 선분 검출 수행**
* **직선의 시작점과 끝점을 반환 -> 선분을 검출한다**
 
**void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap = 0)**
* image: 8비트 단일 채널 입력 영상. 주로 에지 영상을 지정
* **lines: 선분의 시작점과 끝점을 저장할 출력 벡터. 주로 < vec4i > 자료형 변수를 지정**
* rho: 축적 배열에서 픽셀 단위
* theta: 축적 배열에서 라디안 단위
* threshold: 축적 배열에서 직선으로 판단할 임계값
* minLineLength: 검출할 선분의 최소 길이
* maxLineGap: 직선으로 간주할 최대 에지 점 간격
#### 직선 파라미터 정보를 이용하여 영상 위에 빨간색 선분을 그리는 예제 (위와 달리 선분!으로 표시)
<pre><code>
void houghline_segments() {
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat edge;
	Canny(src, edge, 50, 150);

	vector<Vec4i> lines; // 선분의 시작,끝점 x,y좌표 저장
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108456400-96399280-72b3-11eb-9799-25e675984847.png)
### 9.2-2) 허프 변환 원 검출
Step1) **원의 중심 좌표를 찾는다(이 과정에서 축적배열 사용. 원주상의 모든 점에서 그래디언트 방향으로 직선. 원의 중심 부근 축적 값 high)**
Step2) **적합한 반지름을 구한다(center구한 후 원주상에 충분한 edge가 있는지 확인하고 결정)**
>**HoughCircles() 함수를 이용한 허프 변환 원 검출 수행**
**void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius = 0, int maxRadious = 0)**
* image: 8비트 단일 채널 입력 영상. **에지 영상이 아닌 원본 grayscale영상 사용!**
* **circles: 원의 중심(x,y), 반지름, (축적배열누적값). 주로 < vec3f >, < vec4f > 자료형 변수를 지정**
* method: Hough_Fradient만 지정 가능
* dp: 입력 영상과 축적 배열의 크기 비율
* minDist: 인접한 원 중심의 최소 거리
* param1: Canny edge 검출기의 높은 임계값 (낮은 임계값은 param1의 절반값으로 사용)
* param2: 축적 배열에서 원 검출을 위한 임계값
* minRadius: 검출할 원의 최소 반지름
* maxRadius: 검출할 원의 최대 반지름
#### Example) 동전 검출!!

