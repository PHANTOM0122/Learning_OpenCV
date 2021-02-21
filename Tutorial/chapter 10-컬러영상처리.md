컬러 영상 처리
=================
## 10-1) 컬러 영상 다루기
### 10-1-1) 컬러 영상의 픽셀 값 참조
* imread() 함수를 통해 컬러 영상 정보 얻음
* B,G,R 각 생상 성분 값은 uchar 자료형을 사용하여 표현
* **vec3b자료형을 이용하여 B,G,R 표현 / vec3b& pixel = img.at<vec3b>(0,0);**
* **vec3b class를 통해 B,G,R 값 표현 / uchar b1 = pixel[0](B), uchar b2 = pixel[1](G), uchar b3 = pixel[3](R)**
* pointer를 이용하여서도 표현 가능. 
<pre><code>
vec3b * ptr = img.ptr<vec3b>(0); // 0번째 시작 픽셀주소
uchar b2 = ptr[0][0] // (0,0)의 좌표 픽셀의 B
uchar g2 = ptr[0][1] // (0,0)의 좌표 픽셀의 G
uchar r2 = ptr[0][2] // (0,0)의 좌표 픽셀의 R 
</code></pre>
#### Example code) 컬러 영상의 픽셀값 반전
<pre><code>
void colorInverse() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type()); // 반전된 영상 저장할 dst영상

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			//invesere color
			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}</code></pre>
![image](https://user-images.githubusercontent.com/50229148/108613589-cfe6d680-7436-11eb-85d3-92e542d803b5.png)
### 10-1-2) 색 공간 변환
> **void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0;)**
* src: 입력영상
* dst: 결과영상
* code: 색 공간 변환 코드
* dstCn: 결과 영상의 채널 수
* ![image](https://user-images.githubusercontent.com/50229148/108624608-49a7b000-7489-11eb-9d5d-a9269d72442c.png)

#### BGR2GRAY 와 GRAY2BGR
* **BGR2GRAY는 영상의 메모리를 아껴서 연산 속도 향상 시킨다**
* **GRAY2BGR은 흑백영상을 컬러영상으로 변환**

#### BGR2HSV 와 HSV2BGR
* 
