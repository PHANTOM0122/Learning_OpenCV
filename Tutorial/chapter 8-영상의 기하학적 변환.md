영상의 기하학적 변환
========================
## 8.1) 어파인 변환(Affine Transform)
* **영상의 평행 이동, 확대 및 축소, 회전 등의 조합으로 만들 수 있는 기하학적 변환**
* 영상의 확대 및 축소, 회전은 전처리 과정으로 많이 사용되므로 중요하다
### 8.1-1) 어파인 변환
![image](https://user-images.githubusercontent.com/50229148/108205798-e0fac380-7168-11eb-9a77-eacb3eafe8ba.png)
* 어파인 변환 행렬을 구하기 위해서는 최소 3개의 점을 알아야 한다
* **OpenCV는 어파인 변환 행렬을 구하는 함수와 어파인 변환을 통한 실제 영상을 어파인 변환하는 함수를 모두 제공**
> **getAffineTransform (어파인 변환 행렬 구하는 함수)**
<pre><code>
Mat getAffineTransform(const Point2f src[], const Point2f dst[]);
Mat getAffineTransform(InputArray src, InputArray dst);
</code></pre>
* src: 입력 영상에서의 3점의 좌표
* dst: 결과 영상에서의 3점의 좌표
* 반환값: 2x3어파인 행렬. CV_64FC1
> **warpAffine (어파인 변환된 영상을 구하는 함수)**
<pre><code>
void warpAffine(InputArray src, OutputArray dst, InputArray M, Size dsize, int flags = INTER_LINEAR, 
int borderMode = BORDER_CONSTANT, const Scalar& borderValue = Scalar());</code></pre>
* src: 입력영상
* dst: 결과영상. src과 같은 타입이고 크기는 dsize에 의해 결정
* dsize: 결과영상의 크기
* flags: 보간법 알고리즘. 만약 OR연산자를 이용하여 WARP_INVERSE_MAP 플래그를 함께 지정하면 역방향으로 변환 수행
* borderMode: 가장자리 픽셀 확장 방식. BorderTypes 열거형 상수 중 하나를 지정. BORDER_CONSTANT를 지정하면 입력 영상의 픽셀 값이 복사되지 않는 영역은 dst픽셀값을 그대로 유지
* borderValue: borderMode가 BORDER_CONSTANT일 때, 사용할 상수값. 기본값으로 검은색이 지정.
#### Exmaple code
<pre><code>
void affine_transform()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0); // 영상 좌측 상단
	srcPts[1] = Point2f(src.cols - 1, 0); // 영상 우측 상단
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1); // 영상 우측 하단

	// dst 영상은 평행사변형
	dstPts[0] = Point2f(50, 50); // 출력 영상 좌측 상단
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows-50);

	// Get Affine matrix
	Mat M = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108209648-e4447e00-716d-11eb-8bee-9f364457e7fe.png)
