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
void warpAffine(InputArray src, OutputArray 
