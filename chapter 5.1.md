Chapter 5.1 영상의 밝기 조절
====================================

### OpecCV에서 제공하는 영상의 밝기 조절 기법과 직접 영상의 픽셀 값을 참조하여 밝기 조절하는 방법 설명

### 5.1.1 그레이스케일 영상 다루기

> 많은 영상 처리 알고리즘은 그레이스케일 영상을 주 대상으로 한다.

##### Example code // lenna 사진을 grayscale로 불러오기
<pre>
<code>
Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
Mat img2(480, 640, CV_8UC1, Scalar(0)); // 픽셀값이 0으로 초기화된 그레이스케일 영상
Mat img3 = imread("lenna.png", IMREAD_COLOR);
Mat img4;
cvtColor(img3, img4, COLOR_BGR2GRAY); 
</code>
</pre>
* **cvtColor(입력영상, 출력영상, 컬러변환 코드)**

### 5.1.2 영상의 밝기 조절

> **dst(x,y) = src(x,y) + n**
  * dst는 출력영상, src는 입력영상, n은 조절할 밝기 값을 나타낸다. n>0 이면 밝기 증가, n<0이면 밝기 감소.
  * 원소 자료형이 최대,최소값을 벗어나는 경우를 포화연산이라 한다. 실제 영상 밝기 조절을 구현 시, 포화연산을 항상 고려 해야 한다.
  * saturate(x) = 0(x<0일때) // 255(X>255일때) // x (else)
  > ** dst(x,y) = saturate(src(x,y)) + n;
##### Example code // lenna 사진을 brightness +100
<pre>
<code>
Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
Mat dst = src + 100; // or src += 100;
</code>
</pre>

### 5.1.3 영상의 밝기 조절 직접 구현

> **saturate_cast() 함수**
  * **자동으로 포화 연산을 수행한다**
  <pre>
  <code>
  uchar saturate_cast<uchar> (int v)
  </code>
  </pre>
  * v : int자료형 표현할 수 있는 범위의 정수
  * 반환값 : 0~255 정수
##### Example code // lenna 사진을 brightness +100
<pre>
<code>
for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}
</code>
</pre>
  
