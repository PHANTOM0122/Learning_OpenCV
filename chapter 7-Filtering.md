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
  * ksize : Gaussian 커널의 크기. kisze.width,height은 0보다 큰 홀수여야한다. Size()이면 자동으로 커널 크기를 결정한다
  * sigmaX : x방향으로의 가우시안 커널 표준 편차
  * sigmaY : y방향으로의 가우시안 커널 표준 편차. sigmaY = 0이면 sigmaX와 같은 값을 사용한다.
  * borderType : 가장자리 픽셀 확장 방식
  * **표준 편차가 클수록 분산이 되어있다 -> 영상이 더욱 부드럽게 된다**
<pre><code>
void blurring_gaussian() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(0, 0), (double)sigma);
		String desc = format("Guassian: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107513745-00837080-6bec-11eb-92e4-e83fd992ac4d.png)
![image](https://user-images.githubusercontent.com/50229148/107513774-0f6a2300-6bec-11eb-9a16-d7d6f1087ed2.png)
![image](https://user-images.githubusercontent.com/50229148/107513804-1c871200-6bec-11eb-94e2-278de1fba85d.png)
![image](https://user-images.githubusercontent.com/50229148/107513825-26107a00-6bec-11eb-9136-6d139fe23f68.png)
![image](https://user-images.githubusercontent.com/50229148/107513854-2f99e200-6bec-11eb-8240-7f5e1d8bbb40.png)
## 7.3 영상의 Sharpening : 영상 날카롭게 하기!
* **샤프닝은 초점이 잘 맞은 사진처럼 사물의 윤곽이 뚜렷하고 선명한 느낌이 나도록 영상을 변경하는 필터링 기법**
#### 7.3-1) Unsharp mask filter
* Sharpening을 위해서는 영상의 edge 근방에서 pixel의 명암비가 커지도록 수정해야 한다.
* **Sharpening을 위해서는 blurring된 영상을 사용해야 한다**
> **h(x,y) = f(x,y) + alpha * (f(x,y) - f'(x,y)) = (1+alpha)f(x,y) - alpha*f'(x,y) // f' : blurring된 영상**
* alpha(가중치) 영상에 따라 영상의 날카로운 정도를 조절 가능하다
* f(x,y) - f'(x,y) -> edge가 강조된다.
<pre><code>
void unsharp_mask() {
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	imshow("src", src);

	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);
		
		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107518982-ff097680-6bf2-11eb-9a7a-c0694b2bf32d.png)
![image](https://user-images.githubusercontent.com/50229148/107519003-0892de80-6bf3-11eb-96cb-a163c3982363.png)
![image](https://user-images.githubusercontent.com/50229148/107519030-12b4dd00-6bf3-11eb-8db9-63a86a01e51a.png)
![image](https://user-images.githubusercontent.com/50229148/107519050-1a748180-6bf3-11eb-831f-49bb2759c2c9.png)
## 7.4 Noise filtering (잡음 제거 필터링)!
* computer vision의 전처리 과정으로 잡음 제거 필터를 사용한다.
#### 7.4-1) 영상과 잡음 모델
* f(x,y)(영상신호) = s(x,y)(원본신호) + n(x,y)(잡음신호)
* 잡음이 생성되는 방식을 잡음 모델이라 하며, 가장 대표적인 것은 Gaussian 잡음 모델이다.
* **OpenCV 함수를 이용하여 가우시안 모델을 따르는 잡음을 인위적으로 추가할 수 있다**
> **void randn(InputArray dst, InputArray mean, InputArray stddev);
  * dst : Gaussian 난수로 채워질 행렬
  * mean : Gaussian 분포 평균
  * stddev : Gaussian 분표 표준 편차
  * **표준 편차가 작을수록 noise존재 확률 구간이 작아지므로 잡음에 의한 픽셀 값 변화가 적다고 생각할 수 있다**
<pre><code>
void noise_gaussian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	for (int stddev = 10; stddev <= 30; stddev += 10) {
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107521106-7fc97200-6bf5-11eb-87f0-34d36781cc6b.png)
![image](https://user-images.githubusercontent.com/50229148/107521257-abe4f300-6bf5-11eb-9438-0b51d885d620.png)
![image](https://user-images.githubusercontent.com/50229148/107521273-b2736a80-6bf5-11eb-8f29-426d519237db.png)
#### 7.4-2) 양방향 필터
* pixel값이 급격히 변하는 edge근방에 gaussian filter가 적용되는 경우 잡음뿐만 아니라 edge도 함께 감소하게 된다. -> 윤곽도 같이 흐려짐
* **양방향 필터는 에지 성분은 그대로 유지하면서 가우시안 잡음을 효과적으로 제거하는 알고리즘**
* 모든 픽셀 위치에서 주변 픽셀과의 밝기 차이에 의한 고유의 필터 마스크 행렬을 만들어서 마스크 연산을 수행 -> 가우시안보다 연산량이 훨씬 많음
> <code>**void bilateralFilter(Inputarray src, Outputarray dst, int d, double sigmaColor, double sigmaSpace, int boarderType = BORDER_DEFAULT)</code>**
  * d : filtering에 사용할 이웃 픽셀과의 거리. 양수가 아닌 값을 지정하면 sigmaspace로부터 자동 계산
  * sigmaColor : 색 공간에서의 가우시안 필터 표준 편차
  * sigmaSpace : 좌표 공간에서의 가우시안 필터 표준 편차. 값이 클수록 더 많은 주변 픽셀 고려!
  * boarderType : 가장자리 픽셀 확장 방식
<pre><code>
void filter_median()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;}
	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;
	}
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);
	Mat dst2;
	medianBlur(src, dst2, 3);
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107524436-1d727080-6bf9-11eb-9a04-f765fbbee38a.png)
#### 7.4-3) Median-filter
* **미디안 필터는 입력 영상에서 자기 자신, 주변 픽셀 값 중에서 중간값을 선택하여 결과 영상 픽셀값으로 설정한다**
* 특히 잡음 픽셀값이 주변 픽셀 값과 큰 차이가 있는 경우에 효과적으로 동작
> <code>**void medianBlur(Inputarray src, Outputarray dst, int ksize)</code>**
  * src : 입력 영상. ksize에 따라 사용 가능 영상 깊이가 다르다.
  * dst : 출력 영상. src와 같은 크기, 타입을 가진다
  * ksize : 필터 크기. 3과 같거나 큰 홀수를 지정
<pre><code>
void filter_median() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;}
	int num = (int)(src.total() * 0.1);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;} // src 영상에서 10%에 해당하는 픽셀 값을 0또는 255로 설정합니다
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);
	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("GaussianBlur", dst1);
	imshow("medianFilter", dst2);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107526343-18aebc00-6bfb-11eb-89cc-faa34ed438f0.png)
