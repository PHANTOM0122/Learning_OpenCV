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
