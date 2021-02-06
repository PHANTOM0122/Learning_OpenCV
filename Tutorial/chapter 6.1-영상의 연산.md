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
  Mat src1 = imread("aero2.bmp", 
