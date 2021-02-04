효과적인 명암비 조절
==========================
* 영상의 명암비 조절은 전체 픽셀에 적절한 실수를 곱하는 곱셈 연산을 사용한다
* 밝은 영역과 어두운 영역이 골고루 있는 영상일수록 명암비가 높다
* **기본적인 명암비 수식: dst(x,y) = saturate( s X src(x,y))**
  #### 위 수식을 이용할경우 영상이 전반적으로 어두워지거나 밝기가 너무 쉽게 포화되는 단점이 있다.
![result_contrast1](https://user-images.githubusercontent.com/50229148/106914731-a5173580-6748-11eb-8119-834f292de8cb.JPG)
* **효과적인 명암비 수식: dst(x,y) = saturate(src(x,y)+(src(x,y)-128) X alpha)**
  #### 128보다 크면 더 밝고, 작으면 더 작게 만든다. (-1<=alpha<0 이면 명암비가 감소, alpha>0이면 명암비 증가)
![result_contrast2](https://user-images.githubusercontent.com/50229148/106914739-a7798f80-6748-11eb-949c-f9a44457acb2.JPG)
<pre><code>
float alpha = 1.0f;
Mat dst = src + (src-128)*alpha; // * 연산자가 overloading 되어있고 포화 연산 역시 알아서 해준다!
</code></pre>
