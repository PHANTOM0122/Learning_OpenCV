레이블링과 외곽선 검출
========================
## 12.1 레이블링(labeling)
* **영상 내에 존재하는 객체 픽셀 집합에 고유 번호를 매기는 작업**
* **일반적으로 이진화된 영상에서 수행된다. 검은색 픽셀은 배경, 흰색 픽셀은 객체로 간주**
* Grayscale영상을 사용할 경우 pixel이 0인 것만 배경으로 인식하고, 회색 부분은 객체로 인식한다.
> **connectedComponents()함수를 통한 레이블링 영상 출력**
**int connectedComponents(InputArray image, OutputArray labels, int connectivity = 0. int ltype = CV_32S);**
* labels : 출력 레이블 맵 행렬
* connectivity : 연결성. 8 or 4를 지정 가능
* ltype : 출력 행렬 타입. CV_32S or CV_16S 지정 가능
* 반환값 : 레이블 갯수. 반환값이 N이면 0~N-1까지 레이블 넘버가 존재하며 0은 배경이다
<pre><code>
void labeling_basic() {
	uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	Mat src = Mat(8, 8, CV_8UC1, data) * 255;

	Mat labels;
	int cnt = connectedComponents(src, labels); // 객체의 갯수 + 1(배경)

	cout << "src: \n" << src << endl;
	cout << "dst: \n" << labels << endl;
	cout << "number of labels: " << cnt << endl;
}
</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108839633-ad141800-7618-11eb-963f-d42a4a868bef.png)

> **connectedComponentsWithStats() 함수를 통한 레이블 맵 & 객체 영역의 통계 정보 반환**
**int connectedComponentWithStats(image, labels, OutputArray stats, OutputArray centroids, int connectivity=8, int ltype=CV_32S)**
* stats : 각각의 레이블 영역에 대한 통계 정보를 담은 행렬
* centroid : 각각의 레이블 영역의 무게 중심 좌표 정보를 담은 행렬
* 반환값 : label 갯수
![image](https://user-images.githubusercontent.com/50229148/108840644-0466b800-761a-11eb-8c98-05d7f3acc4bf.png)
#### Example) labeling을 이용한 객체의 바운딩 박스 그리기
<pre><code>
void labelint_stats() {
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int i = 1; i < cnt; i++) { // 0은 배경이기 때문
		int* p = stats.ptr<int>(i); // stats 배열

		if (p[4] < 20) continue; // 객체의 픽셀 갯수(면적. 4번째 열)이 20이하면 잡음이라고 간주

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]),Scalar(0,255,255),2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108841622-670c8380-761b-11eb-8ca9-3d511bfcba73.png)
 ## 12.2 외곽선 검출
 * **객체의 외곽선 좌표를 모두 추출하여 계층 정보와 함께 반환**
 ### 12.2-1) 외곽선 검출
 * 외곽선은 객체 영역 픽셀 중에서 배경 영역과 인접한 픽셀을 의미한다
 * **객체 하나의 외곽선 정보는 vector < Point > 타입으로 저장, 하나의 영상에는 여려개의 객체가 있으므로 vector < vector < point > > 타입으로 저장**
 
 ![image](https://user-images.githubusercontent.com/50229148/108852830-6844ad00-7629-11eb-85a2-8721196bebc0.png)
 
 > **findContours()함수를 통한 외곽선 검출**

**void findContours(image, OutputArray contours, OutputArray hierarchy, int mode, int method, Point offset = point());**

**void findContours(image, OutputArray contours, int mode, int method, Point offset = point());**

* image : 8비트 1채널 영상이여야 한다. 보통 threshold() 등 함수에 의해 만들어진 이진 영상을 사용한다.
* contours : 검출된 외곽선 정보.  vector < vector < point > > 타입으로 저장
* hierarchy : 외곽선 계층 정보. vector < Vec4i > 타입의 변수를 지정
* mode : 외곽선 검출 모드. RetrievalModes 열거형 상수를 지정
* mehtod : 외곽선 근사화 방법. 
* offset : 외과선 점 좌표의 오프셋.
* 실제 동작할 때는 입력 영상에서 픽셀 값이 0이 아니면 객체로 간주하여 외곽선을 검출한다.
* hierarchy 인자에는 검출된 외곽선의 계층 정보가 저장되고, 보통 vector<Vec4i> 타입의 변수를 지정한다. Vec4i는 int 자료형 네 개를 저장할 수 있는 OpenCV 벡터 클래스로 i 번째 외곽선에 대해 hierarchy[i][0]에는 다음 외곽선 번호, hierarchy[i][1]에는 이전 외곽선 번호, hierarchy[i][2]에는 자식 외곽선 번호, hierarchy[i][3]에는 부모 외곽선 번호가 저장된다. 만약 계층 구조에서 해당 외곽선이 존재하지 않으면 -1이 저장된다.


RetrievalModes|	설명|
-------|-----------|
RETR_EXTERNAL	|객체 바깥쪽 외곽선만 검색. 계층 구조는 만들지 않는다.
RETR_LIST	|객체 바깥쪽과 안쪽 외곽선을 모두 검색. 계층 구조는 만들지 않는다.
RETR_CCOMP	|모든 외곽선을 검색하고 2단계 계층 구조를 구성
RETR_TREE	|모든 외곽선을 검색하고 전체 계층 구조를 구성


ContoursApporximationModes	|설명|
--------|----------|
CHAIN_APPROX_NONE	|모든 외곽선 점들의 좌표를 저장
CHAIN_APPROX_SIMPLE	|외곽선 중에서 수평선, 수직선, 대각선 성분은 끝점만 저장
CHAIN_APPROX_TC89_L1	|Teh & Chin L1 근사화를 적용
CHAIN_APPROX_TC89_KOCS	|Teh & Chin k cos 근사화를 적용

![image](https://user-images.githubusercontent.com/50229148/108854266-06854280-762b-11eb-8e7b-1ce5c190eb99.png)
![image](https://user-images.githubusercontent.com/50229148/108854284-09803300-762b-11eb-811e-61f42d768a0b.png)

> **drawContours()을 통한 외곽선 그리기**
**void drawContours(image,InputArrayOfArraus contours, int contourIdx, const Scalar& color, int thickness = 1, int lineType = LINE_8, InputArray hierarchy = noArray(), int maxLevel = INT_MAX, Point offset = Point());**
* contourIdx : 외곽선 번호. 음수를 지정하면 전체 외곽선을 그린다
* color : 외곽선 색상 또는 밝기
* thickness : 외과선 두께. FILLED or -1을 지정하면 외곽선 내부를 채운다
* lineType : 외곽선 타입
* hierarchy : 외곽선 계층 정보
* maxLevel : 그릴 외곽선의 최대 레벨. 0이면 지정한 번오만 그리고, 1이상이면 그에 해당하는 하위 레벨까지 그린다
* offset : 지정한 좌표의 크기만큼 외곽선 좌표를 이동하여 그린다
#### 외곽선 검출과 그리기
<pre><code>
void contours_basic()
{
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255); // Random으로 색상을 정함
		drawContours(dst, contours, i, c, 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
} </code></pre>

![image](https://user-images.githubusercontent.com/50229148/108856776-bcea2700-762d-11eb-903c-cf56d0b8f281.png)

#### Exmaple2 외곽선 검출과 그리기
<pre><code>
void contours_hier()
{
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108858049-143cc700-762f-11eb-8d6a-eef13933c022.png)
 ### 12.2-2) 외곽선 처리 함수
1) 주어진 외곽선 점들을 감싸는 가장 작은 크기의 사각형, 즉 바운딩 박스를 구하고 싶다면 boundingRect() 함수를 사용한다.
> Rect boundingRect(InputArray points);
  * points : 입력 점들의 집합
  * return : 입력 점들을 감싸는 최소 크기의 사각형
2) 외곽선 또는 점들을 감싸는 최소 크기의 회전된 사각형을 구하고 싶을 때는 minAreaRect() 함수를 사용한다.
> Rect boundingRect(InputArray points);
  * points : 입력 점들의 집합
  * return : 입력 점들을 감싸는 최소 크기의 회전된 사각형
3) 외곽선 또는 점들을 감싸는 최소 크기의 원을 구하고 싶을 때는 minEnclosingCircle() 함수를 사용한다.
> void boundingRect(InputArray points, Point2f& center, float& radius);
  * points : 입력 점들의 집합
  * center : 중심 좌표
  * radius : 반지름
  * return : 입력 점들을 감싸는 최소 크기의 회전된 사각형
4) 임의의 곡선의 길이를 구하고 싶을 때는 arcLength() 함수를 사용한다.
> double arcLength(InputArray curve, bool closed);
  * curve : 입력 곡선
  * closed : 폐곡선 여부
  * 반환값 : 입력 곡선의 길이
5) 외곽선이 감싸는 영역의 면적을 알고 싶을 때는 contourArea() 함수를 사용한다.
> double contourArea(InputArray contour, bool oriented = false);
  * contour : 입력 곡선
  * oriented : 진행 방향 정보 사용 여부. true이면 (반)시계 방향에 따라 부호가 달라짐. false이면 면적의 절댓값 반환
  * 반환값 : 입력 곡선이 감싸는 면적
6) 외곽선 또는 곡선을 근사화 할 때는 approxPolyDp() 함수를 사용한다.
> void approxPolyDP(InputArray curve, OutputArray approxCurve, double epsilon, bool closed);
  * epsilon : 근사화 정밀도 파라미터
  * closed : 폐곡선 여부.
* **더글라스-포이커 알고리즘을 이용한다.**
더글라스 포이커 :입력 외곽선에서 가장 멀리 떨어져 있는 두 점을 찾아 직선으로 연결하고, 해당 직선에서 가장 멀리 떨어져 있는 외곽선 상의 점을 찾아 근사화 점으로 추가한다.
![image](https://user-images.githubusercontent.com/50229148/108860390-7d253e80-7631-11eb-81d7-b74ca47eb557.png)
<pre><code>
// pts 외곽선 주변에 바은딩 박스를 그리고 label 문자열을 출력합니다
void setLabel(Mat& img, const vector<Point>& pts, const String& label) {
	Rect rc = boundingRect(pts);
	rectangle(img, rc, Scalar(0, 0, 255), 1);
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

int main(int argc, char* argv[])
{
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	for (vector<Point> pts : contours) {
		if (contourArea(pts) < 400)
			continue;

		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

		int vtc = (int)approx.size();

		if (vtc == 3) {
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4) {
			setLabel(img, pts, "RECT");
		}
		else { // 객체의 면적 대 비율을 조사하여 원에 가까우면 주변에 바운딩 박스를 구함
			double len = arcLength(pts, true);
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);

			if (ratio > 0.85) {
				setLabel(img, pts, "CIR");
			}
		}
	}

	imshow("img", img);

	waitKey(0);
	return 0;
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108861869-06894080-7633-11eb-9be9-460b7f817219.png)
