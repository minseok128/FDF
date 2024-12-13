# FDF
2차원 배열 형태의 N x M 크기의 map을 인자로 받아 점들을 선으로 이어 3D wireframe model 을 렌더링하는 프로그램

## 사용법
### 프로그램 실행
```
./fdf test_maps/MAP
```

- 위 형식에서 MAP 에 원하는 .fdf 파일을 넣어주면 실행된다.
- test_maps 폴더가 아니더라도 .fdf 파일을 형식에 맞게 만든 map 파일이 있다면 인자로 줄 수 있다.

  
### 내부 조작 (bonus)
- object translation
  - W: object 위로 이동
  - S: object 아래로 이동
  - A: object 왼쪽으로 이동
  - D: object 오른쪽으로 이동
    
- object scale
  - Q: object 축소
  - E: object 확대
    
- object rotation (x축, y축, z축 회전을 순서대로 적용)
  - Z: object z축 회전
  - X: object x축 회전
  - C: object y축 회전
    
- object projection
  - mouse left click: isometric projection
  - mouse right click: parallel projection

## Input map 형식
<img width="679" alt="스크린샷 2024-06-25 오후 7 03 42" src="https://github.com/seonjo1/FDF/assets/127729846/f033076a-cfe7-4c09-9202-c523d25eeb9d">

- 위 그림과 같이 N x M 형식의 map
- 가로는 x, 세로는 y, 내부 값은 z로 (x, y, z) 가 하나의 point
- 확장자는 반드시 .fdf
- z 값 뒤에 color가 존재하면 색 적용

## 렌더링 결과
### test_maps/julia.fdf 맵 파일을 Rendering 한 결과

**isometric projection**

<img width="1918" alt="스크린샷 2024-06-25 오후 7 23 53" src="https://github.com/seonjo1/FDF/assets/127729846/d5b67ee3-19a1-4992-8d88-64b1676f88be">

**parallel projection**

<img width="1919" alt="스크린샷 2024-06-25 오후 7 26 55" src="https://github.com/seonjo1/FDF/assets/127729846/226245ed-b6a7-4620-a7e5-dcf99fb644ec">

## 렌더링 방법
- mlx 라는 그래픽 라이브러리를 사용
- 렌더링 순서
  - 기존 map 정보의 복사본 생성
  - x, y, z 회전 값을 이용해 복사본에 회전 변환 적용 (z -> x -> y 순서)
  - 좌표계 원점을 window 왼쪽 위에서 가운데로 이동
  - object가 화면 가운데로 오는 기준으로 x, y의 이동 값을 수정
  - 복사본을 원점 좌표계로 변환하고 이동 값을 적용하여 카메라 뷰로 전환
  - 복사본을 bresenham 알고리즘으로 가로선 렌더링
  - 복사본을 bresenham 알고리즘으로 세로선 렌더링
- z 값을 기준으로 렌더링 우선순위 설정 (화면으로 나오는 방향으로 +z)
  - 우선순위 설정이 없으면 가까이있는 선이 멀리있는 선에 의해 가려지는 현상 발생
  - z 버퍼를 이용하려 했으나 딜레이 때문에 실패
  - N x M 크기의 map을 기준으로 (0, 0)과 (N - 1, M - 1)의 z 값 비교
  - (0, 0)의 z 값이 작으면 (0, 0)부터 가로줄, 세로줄 렌더링 시작 
  - (N - 1, M - 1)의 z 값이 작으면 (N - 1, M - 1)부터 가로줄, 세로줄 렌더링 시작

## build
```
make
```
- fdf 프로그램 생성
  
```
make bonus
```
- fdf 프로그램 생성 (upgrade 버전)

```
make clean
```
- fdf 생성시 만들어진 .o 파일들 삭제

```
make fclean
```
- make clean + fdf 파일 삭제

```
make re
```
- make fclean + make
