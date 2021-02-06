영상의 산술 및 논리 연산
=================================
## 영상의 산술 연산
* 영상은 일종의 2차원 행렬이기 때문에 서로 더하거나 빼는 연산 수행이 가능하다
> **dst(x,y) = saturate(src1(x,y)+src2(x,y))**
  * **OpenCV에서는 add()함수를 이용하여 영상의 덧셈 수행이 가능하다**
  <pre><code>
  void add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
  </code></pre>
  * scr1, src2 : 입력 행렬 또는 Schalar
  * dst : 입력 행렬과 같은 채널 수를 갖는 출력 행렬. dst의 깊이는 src1,src2의 깊이와 같거나 dtype인자에 의해 결정
  * mast : 8비트 1채널의 매스크 영상. mask 원소값이 0이 아닌 위치에서만 덧셈연산 수행
  * dtype : dst가 src1,src2와 깊이가 같은 경우에는 -1을 지정가능. src1,2가 서로 다른 경우는 반드시 지정해야 한다.
  ##### Example code
  <pre><code>
  Mat src1 = imread("aero.bmp", IMREAD_GRAYSCALE);
 	Mat src2 = imread("camera.bmp", IMREAD_GRAYSCALE);
	 Mat dst;
	 add(src1, src2, dst);
 	// or
 	dst = src1 + src2;
  </code></pre>
> **dst(x,y) = saturate(alpha * src1(x,y) + beta * src2(x,y) + gamma)**
  * alpha + beta = 1인 경우 영상에서 포화되는 픽셀이 발생하지는 않으며, >1인 경우는 입력영상보다 밝아지고, <1이면 어두운 영상이 생성
  * 두 영상의 가중치 합을 구하려면 **addWeighted() 함수**를 사용한다.
  <pre><code>
  void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype = -1);
  </code></pre>
  * gamma : 가중합 결과에 추가적으로 더할 값
  <pre><code>
  Mat src1 = imread("aero.bmp", IMREAD_GRAYSCALE);
 	Mat src2 = imread("camera.bmp", IMREAD_GRAYSCALE);
	 Mat dst;
	 addweighted(src1, 0.5, src2, 0.5, dst);
  </code></pre>
> **dst(x,y) = saturate(src1(x,y) - src2(x,y))**
  * 두 영상의 차를 나타낸다.
  <pre><code>
  void substract(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
  </code></pre>
> **dst(x,y) = |src1(x,y) - src2(x,y)|**
 * **차영상은 두 개의 영상에서 변화가 있는 영역을 찾아낸다**
  <pre><code>
  void absdiff(InputArray src1, InputArray src2, OutputArray dst);
  </code></pre>
  <pre><code>
  add(src1, src2, dst1);
  addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
  subtract(src1, src2, dst3);
  absdiff(src1, src2, dst4);
  </code></pre>
![image](https://user-images.githubusercontent.com/50229148/107119891-c5bcc800-68cd-11eb-9221-29989f03b3e0.png)

## 영상의 논리 연산
<pre><code>
void bitwise_and(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
void bitwise_or(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
void bitwise_xor(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
void bitwise_not(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);
</code></pre>
![image](https://user-images.githubusercontent.com/50229148/107119862-9c9c3780-68cd-11eb-8b89-6eace07152fc.png)


