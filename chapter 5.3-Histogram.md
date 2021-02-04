Histogram
==================
* **Histogram: 영상의 픽셀 값 분포를 그래프 형태로 표현한 것을 의미!**
  * openCv에서는 histogram을 구하기 위해서 calcHist() 함수를 사용!
  #### 영상의 히스토그램 구하기
  <pre><code>
  Mat calcGrayHist(const Mat& img)
	{CV_Assert(img.type() == CV_8UC1); // 함수로 전달된 img영상이 grayscale영상인지 확인!
	Mat hist;
	int channels[] = { 0 }; // 채널 번호를 담은 배열. grayscale은 1개의 채널이므로 0하나만 원소로 갖는다.
	int dims = 1; // 결과로 구해지는 행렬이 1차원 행렬임을 나타냄
	const int histSize[] = { 256 }; // 입력 영상의 첫번째 채널 값의 범위를 256개 빈으로 나누어 히스토그램 생성!
	float graylevel[] = { 0, 256 }; // 배열의 원소에 grayscale 값의 최솟값과 최댓값인 0과 256을 차례로 지정.
	const float* ranges[] = { graylevel }; // graylevel 배열 이름을 원소로 갖는 배열이다.
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges); 
	return hist;}
  </code></pre>
  #### 영상의 히스토그램 그래프 그리기
  <pre><code>
  Mat getGrayHistImage(const Mat& hist)
  {CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));
	double histMax;
	minMaxLoc(hist, 0, &histMax); // 행렬 원소의 최댓값을 찾는다
	Mat imgHist(100, 256, CV_8UC1, Scalar(255)); // 흰색으로 초기화된 256X100영상을 만든다
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0)); // 각각의 빈에 대한 히스토그램 그래프를 구한다.
	}
	return imgHist;}
  </code></pre>
  #### 히스토그램 스트레칭
  * **영상의 히스토그램이 그레이스케일 전 구간에 걸쳐서 나타나도록 변경하는 선형 변환 기법**
  * **dst(x,y) = (src(x,y)-G(min)) * 255 / G(max)-G(min)**
  <pre><code>
  double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	Mat dst = (src - gmin) * 255 / (gmax - gmin);
  </code></pre>
  ![result_histogramstretching](https://user-images.githubusercontent.com/50229148/106925553-89655c80-6753-11eb-8e7a-c95407038a86.JPG)
  #### 히스토그램 평활화
  * **영상의 픽셀 값 분포가 전체 영역에서 골고루 나타나도록 변경**
  * **dst(x,y) = round(H(src(x,y)) * L(max) / N)**
  * **평활화를 수행하는 void eqaulizeHist(InputArray src, OutputArray dst);**
  <pre><code>
  Mat dst;
	equalizeHist(src, dst);
  </code></pre>
  ![result_histogramequalization](https://user-images.githubusercontent.com/50229148/106925522-823e4e80-6753-11eb-85de-6473d0e2de33.JPG)
    
