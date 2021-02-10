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
