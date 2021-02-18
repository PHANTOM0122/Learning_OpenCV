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
* > **transform (영상 전체를 사용않고 일부 점들이 어디로 이동하는지 구하는 함수)**
<pre><code>
void transform(InputArray src, OutputArray dst, InputArray m);</code></pre>
* src: 입력 행렬 또는 vector<point2f>점의 좌표를 다채널로 표현
* dst: 출력 행렬 또는 vector<Point2f>
* m: 변환 행렬. 2x2 or 2x3 실수형 행렬.
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
	
	//transform
	vector<Point2f> src = {Point2f(100,20) , Point2f(200,50)};
	vector<Point2f> dst;
	transform(src,dst,M);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108209648-e4447e00-716d-11eb-8bee-9f364457e7fe.png)
### 8.1-2) 이동 변환
* **영상을 가로 또는 세로 방향으로 일정 크기만큼 이동시키는 연산을 의미하며 시프트 연산이라고도 한다**
* 영상을 x방향으로 a, y방향으로 b만큼 이동시키는 어파인 변환 행렬은 아래와 같다

![image](https://user-images.githubusercontent.com/50229148/108223894-a94a4680-717d-11eb-8c70-a7467007d843.png)

#### 영상을 가로 150 세로 100 pixel만큼 이동시키는 이동변환 code
<pre><code>
void affine_translation()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// 가로로 150 pix, 세로로 100 pix 만큼 이동 
	Mat M = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 });

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108224868-b451a680-717e-11eb-8d8a-70d6a38b276f.png)
### 8.1-3) 전단 변환
* **직사각형 형태의 영상을 한쪽 방향으로 밀어서 평행사변형 모양으로 변형되는 변환**
* 전단 변환은 픽셀이 어느 위치에 있는가에 따라 이동 정도가 달라진다.
* **x좌표가 증가함에 따라 영상이 조금씩 세로 방향으로 이동하는 변환의 수식은 다음과 같다**

![image](https://user-images.githubusercontent.com/50229148/108226687-7786af00-7180-11eb-99f9-bd7bb529fcc0.png)
* **y좌표가 증가함에 따라 영상이 조금씩 가로 방향으로 이동하는 변환의 수식은 다음과 같다**

![image](https://user-images.githubusercontent.com/50229148/108226848-9b49f500-7180-11eb-9c1d-759a142ed31b.png)

![image](https://user-images.githubusercontent.com/50229148/108227024-cc2a2a00-7180-11eb-8df9-34e3d77ad824.png)
#### Example) 영상 y좌표가 증가함에 따라 x좌표에서 0.3y만큼 밀린 원본 영상 픽셀이 나타나기 시작하는 진단변환
<pre><code>
void affine_shear()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	double mx = 0.3;
	// y좌표가 증가함에 따라 0.3y에 해당하는 x좌표에서 원본 영상 픽셀이 나타남
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 });

	Mat dst;
	// 전단 변환에 의해 짤리지 않도록 가로 크기를 cvRound 이용하여 조절
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108228312-15c74480-7182-11eb-9c4e-e569a212b5ed.png)
### 8.1-4) 크기 변환
* **영상의 전체적인 크기를 확대 또는 축소**
* sx or sy > 1이면 영상 확대 / < 1이면 영상 축소

![image](https://user-images.githubusercontent.com/50229148/108232983-ac960000-7186-11eb-9f41-31a877006756.png)

![image](https://user-images.githubusercontent.com/50229148/108233141-d4856380-7186-11eb-9f77-5d93839201ad.png)
#### resize() 함수를 통한 영상 크기 조정
> **void resize(InputArray src, OutputArray dst, Size dsize, double fx = 0; double fy = 0; int interpolation = INTER_LINEAR);**
* dsize : 출력 영상 크기
* fx : x축 방향으로의 크기 변환 비율. dsizedp Size()를 지정한 경우에 사용.
* fy : y축 방향으로의 크기 변환 비율. dsizedp Size()를 지정한 경우에 사용.
* interpolation: 보간법 지정. 
열거형 상수 설명
1. INTER_NEAREST	최근방 이웃 보간법 - 가장 빠르게 동작하지만 화질이 안좋음
2. INTER_LINEAR		양선형 보간법 - 속도기 빠르고 화질도 좋아서 널리 활용
3. INTER_CUBIC		3차 보간법 - 화질에 focus
4. INTER_AREA		픽셀 영역 리샘플링 - 축소시 무아래 현상이 적게 발생하여 화질에 좋음
5. INTER_LANCZOS4	8×8 이웃 픽셀을 사용하는 란초스(Lanczos 보간법) - 화질에 focus
#### Example) 다양한 보건법을 이용한 영상 확대 결과 비교
<pre><code>
void affine_scale()
{
	Mat src = imread("rose.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST); // x,y 비율 4배 확대
	resize(src, dst2, Size(1920, 1280)); // Size()를 이용한 4배 확대
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC); // 3차 보간법
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4); // 란초스 보간법


	imshow("src", src);
	imshow("dst1", dst1(Rect(400,500,400,400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108235046-ccc6be80-7188-11eb-89ec-9dacb1b1352e.png)
### 8.1-5) 회전 변환
* **특정 좌표를 기준으로 영상을 원하는 각도만큼 회전하는 변환**
* 아래는 원점을 기준으로 반시계 방향으로 영상을 회전하는 어파인 변환 행렬

![image](https://user-images.githubusercontent.com/50229148/108304408-53ac8300-71eb-11eb-82af-cb1a01ffefa8.png)

![image](https://user-images.githubusercontent.com/50229148/108304353-35df1e00-71eb-11eb-9487-167284ca0db1.png)
#### getRotationMatrix2D() 함수를 이용한 회전변환
* **원점이 아닌 특정 좌표를 기준으로 회전시키거나 크기 변환까지 같이 해주는 함수**
> **Mat getRotationMatrix2D(Point2f center, double angle, double scale)**
  * center : 회전 중심 좌표
  * angle : 회전 각
  * scale : 회전후 추가적으로 확대/축소 시킬 비율. 크기를 유지하기 위해서는 1
  * return : 2X3 Affine matrix
<pre><code>
void affine_rotation() {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	Mat M = getRotationMatrix2D(cp, 20, 1); // Rotate 20 degree. same Size!

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108304734-fc5ae280-71eb-11eb-976a-73211d41c801.png)
### 8.1-6) 대칭 변환
* 상하/좌우 대칭 -> 출력 영상은 입력 영상과의 pixel이 1:1 대응이 되므로 보간법이 필요하지 않다
* 좌우대칭
![image](https://user-images.githubusercontent.com/50229148/108306254-22ce4d00-71ef-11eb-9d47-32e672db1241.png)

* 상하대칭
![image](https://user-images.githubusercontent.com/50229148/108306260-26fa6a80-71ef-11eb-8bad-0abb2f0380af.png)
#### flip() 함수를 이용한 회전변환
> **void flip(InputArray src, OutputArray dst, int flipcode)**
  * **flipcode: 양수이면 좌우, 0이면 상하, 음수이면 좌우/상하 대칭 모두 수행(=180도 회전)**
<pre><code>
void affine_filp() {
	Mat src = imread("eastsea.bmp");
	
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	int flipcode[] = { -1,0,1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipcode[i]);

		String desc = format("flipcode: %d", flipcode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255,0,0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108306074-c4a16a00-71ee-11eb-9351-985930c0164b.png)
![image](https://user-images.githubusercontent.com/50229148/108306112-dbe05780-71ee-11eb-9aba-0758e390a635.png)
![image](https://user-images.githubusercontent.com/50229148/108306098-d2ef8600-71ee-11eb-952e-4a73dfe919e3.png)
