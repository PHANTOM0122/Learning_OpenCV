Filtering
================
## 7.1 영상의 필터링
#### 7.1-1) 필터링 연산 방법
> <code>**void filter2D(Inputarray src, Outputarray dst, int ddepth, Inputarray kernel, Point anchor = Point(-1,-1), double delta =0, int boarderType = BORDER_DEFAULT)**</code>
  * src : 입력영상
  * dst : 출력영상
  * ddepth : 결과 영상의 깊이
  * kernel : 필터링 커널(필터링 성격을 정의하는 행렬). 1채널 실수형 행렬
  * anchor : 고정점 좌표. Point(-1,-1)을 지정하면 커널 중심을 고정점으로 사용
  * delta : 필터링 연산 후 추가적으로 더할 값
  * borderType : 가장자리 픽셀 확장 방식
#### 7.1-2) 엠보싱 필터링
* **대각선 방향으로 픽셀 값이 급격하게 변하는 부분에서 결과 영상 픽셀 값이 0보다 훨씬 크거나 훨씬 작은 값을 가지게 된다.**
* **평탄한 영역에선 픽셀값이 0에 가까운 값을 가지게 됩니다**
* 음수값은 포화 연산에 의해 0이 되어버리므로, 보통 **delta = 128을 더하는 것이 보기에 좋다**
* 아래와 같이 장미꽃 경계부분은 입체감있게, 완만하게 바뀌는 곳은 128로 가까운 회색으로 표현
<pre><code>
void filter_embossing()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;}

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("src", src);	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107510240-00cd3d00-6be7-11eb-9bca-73f74803eba4.png)
## 7.2 영상의 블러링 : 영상 부드럽게 하기!
* **blurring은 초점이 맞지 않는 사진처럼 영상을 부드럽게 만드는 필터링 기법이며, smoothing이라고도 한다**
#### 7.2-1) 평균값 필터
* 특정과 주변 픽셀들의 산술 평균을 결과 영상 픽셀값으로 설정
* 픽셀값의 급격한 변화가 줄어들어 날카로운 에지가 무너지고 잡음의 영향이 줄어드는 효과
* 과도하게 사용시 사물의 경계가 흐려지고 사물의 구분이 어려워진다
> <code>**void blur(Inputarray src, Outputarray dst, Size ksize, Point anchor = Point(-1,-1), int boarderType = BORDER_DEFAULT)</code>**
  * src : 입력영상
  * dst : 출력영상
  * ksize : 블러링 커널의 크기
  * anchor : 고정점 좌표. Point(-1,-1)을 지정하면 커널 중심을 고정점으로 사용
  * borderType : 가장자리 픽셀 확장 방식
<pre><code>
void blurring_mean() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);
	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));
		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107512328-04ae8e80-6bea-11eb-9c6f-6f38939cfe40.png)
![image](https://user-images.githubusercontent.com/50229148/107512352-0f692380-6bea-11eb-83a8-18ef36fd2a12.png)
![image](https://user-images.githubusercontent.com/50229148/107512376-17c15e80-6bea-11eb-9a80-87385897c025.png)
### 7.2-2) Gaussian Filter
* **평균값 필터보다 더 자연스러운 blurring 기법이다**
> <code>**void GaussianBlur(Inputarray src, Outputarray dst, Size ksize, double sigmaX, double sigmaY, int boarderType = BORDER_DEFAULT)</code>**
  * src : 입력영상
  * dst : 출력영상
  * ksize : Gaussian 커널의 크기. kisze.width,height은 0보다 큰 홀수여야한다. 
  * sigmaX : x방향으로의 가우시안 커널 표준 편차
  * sigmaY : y방향으로의 가우시안 커널 표준 편차
  * borderType : 가장자리 픽셀 확장 방식
<pre><code>
