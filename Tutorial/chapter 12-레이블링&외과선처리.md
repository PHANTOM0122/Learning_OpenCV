레이블링과 외곽선 검출
========================
## 12.1 레이블링(labeling)
* **영상 내에 존재하는 객체 픽셀 집합에 고유 번호를 매기는 작업**
* **일반적으로 이진화된 영상에서 수행된다. 검은색 픽셀은 배경, 흰색 픽셀은 객체로 간주**
> **connectedComponents()함수를 통한 레이블링 영상 출력**
**int connectedComponents(InputArray image, OutputArray labels, int connectivity = 0. int ltype = CV_32S);**
* labels : 출력 레이블 맵 행렬
* connectivity : 연결성. 8 or 4를 지정 가능
* ltype : 출력 행렬 타입. CV_32S or CV_16S 지정 가능
* 반환값 : 레이블 갯수. 반환값이 N이면 0~N-1까지 레이블 넘버가 존재하며 0은 배경이다

