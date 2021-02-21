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
