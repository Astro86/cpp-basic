# 과제 내용 및 제한 사항

![img5](https://user-images.githubusercontent.com/35681772/60001080-9d546b80-96a0-11e9-8502-662c785b1b18.png)

![img6](https://user-images.githubusercontent.com/35681772/60000302-e2779e00-969e-11e9-8c2c-cca5ef65301d.png)

![img7](https://user-images.githubusercontent.com/35681772/60000304-e2779e00-969e-11e9-8551-7637b4f171b1.png)

![img8](https://user-images.githubusercontent.com/35681772/60000306-e2779e00-969e-11e9-87fc-47217795f661.png)

---

# 과제 구현 결과

## 1. 개요

설계의 목적, 요구사항, 개발환경 등 기본 사항들을 정리
(개발환경은 학생 개개인의 개발환경을 작성하되, 구현은 채점서버에 맞게 구현해야 함)

### 1-1. 설계의 목적

다익스트라 알고리즘을 이용하여 출발지부터 목적지까지의 침수지역을 경유하지 않는 최단 거리
및 경로를 제공하고자 함.

### 1-2. 요구사항
제한사항에 맞춰 다익스트라 알고리즘을 이용하여 최단 거리 및 경로를 찾고, 이 알고리즘을 이
용할 때 decreaseKey() 함수는 정점의 최단거리가 더 작아지는 경우에만 수행할 것.
그래서 그렇게 찾은 최단 거리와 경로를 ‘질의형식’에 맞춰 적절히 화면에 표현해준다.

### 1-3. 개발환경

>OS : Windows 10 Pro<br>
Processor : Intel(R) Core(TM) i7-5557 CPU @ 3.10GHz<br>
RAM : 16GB<br>
IDE : Microsoft Visual Studio Community 2017 ver 15.9.9<br>
Language : Visual C++ 2017<br>

---

## 2. 필요한 자료구조 및 기능

### 2-1. 필요한 자료구조

STL을 사용한 자료구조는 vector와 priority queue를 사용하였고, 인자로 pair쌍 또는 tuple쌍으
로 받아 적절하게 처리하였다. 그 외 int형 배열과 같은 기본형 자료구조를 사용하였다.

Vector 자료구조를 사용하여 주어진 input에 대해 결과값을 출력할 때 까지 데이터를 담고 있는
변수는 두개만 선언하였다.

먼저 vertex_info 변수는 vertex 정보를 담아두고 있다. tuple쌍으로 데이터를 받고 있고 tuple은 지역번호, 지역명, 침수여부 순서로 데이터를 받고있다.

특이사항으로 input에서 지역번호가 고유값 즉, key 역할을 하고있는데 이 값의 범위가 100000
부터 999999 까지이기 때문에 이 key값의 범위를 모두 포함하는 정적 변수를 선언하면 불필요
한 공간이 낭비될 여지가 있어서 입력으로 들어오는 key값을 0부터 차례대로 새로운 key값을 부
여하였고, 그 대응 정보를 indexContainer 라는 int형 배열에 담아두었다.

그래서 indexContainer[지역번호]의 값이 새로 부여된 key값을 나타내고 반대로, vertex_info 벡
터에 0부터 차례대로 vertex 정보가 입력되었으므로 get<0>(vertex_info[새로운 key값]) 과 같
이 사용하면 원래의 지역번호를 리턴받을 수 있도록 구현하였다.

### 2-2. 기능

문제의 요구사항을 구현하는 데에 있어 필요한 기능은 다음과 같다.

1) 최단 거리를 찾기 위해 다익스트라 알고리즘 구현에 있어 최소 weight 값을 얻어내는 기능

2) 최단 경로를 찾아내기 위해 Predecessor 를 추적하여 도착지에서부터 출발지까지의 정보를 얻고 그 것을 다시 출발지부터 도착지까지의 순서로 출력하는 기능

---

## 3. 기능별 알고리즘 명세

### 3-1. 기능을 위한 알고리즘 설명(복잡도 분석)

우선 다익스트라 알고리즘에 있어 최소 weight값을 얻어낼 때 우선순위 큐를 사용하여 구현하였
다. STL의 우선순위 큐를 가져다 사용하였는데, 실제 구현체를 확인해 보니 heap을 이용하여 구현이 되어있었다. 수업 시간에 배운 내용을 토대로 heap을 이용하여 구현한 priority queue의 복잡도는 다음과 같다.

 -  insert() : O(logN)
 -  removeMin(or removeMax)() : O(logN)
 -  getMin(or getMax)() : O(1)
 -  decreaseKey() : O(logN)

따라서 다익스트라 알고리즘에서 모든 vertex는 많아야 한번 방문되고 그러므로 priority queue
에 insert() 또는 deleteMin() 되는 횟수도 많아야 한번이 된다. 즉, insert()연산과 deleteMin()연산은 O(N)번 수행된다고 할 수 있다.

decreaseKey() 연산은 각 edge 마다 최악의 경우 edge의 양 끝 vertex가 모두 참조하는 경우
이므로 최대 2M번 즉, O(M)번 수행된다고 할 수있다.

결과적으로 heap으로 구현한 priority queue를 이용한 다익스트라 알고리즘은 O(NlogN) +
O(MlogN) 의 시간복잡도를 갖는데 이는 O(MlogN)에 bound되어 O(MlogN)의 시간복잡도를 갖
게 된다.

그리고 predecessor를 추적하여 도착지에서부터 출발지까지의 정보를 얻어내는 기능은 위에 언
급한 것 처럼 구현은 vector로 하였으나 개념상 stack의 기능을 수행한다. 

따라서 다익스트라 알고리즘을 수행하며 decreaseKey() 가 진행될 때 O(MlogN)의 시간복잡도를 갖고, tree set에 모든 vertex가 들어있으며 이를 stack의 pop을 이용하여 거꾸로 빼 내는데에 O(N)의 시간복잡도를 갖게 된다. 

따라서 O(MlogN) + O(N)은 O(MlogN)에 bound 되므로 이 기능 또한 O(MlogN)의 시간복잡도를 갖는다.


---

## 4. 평가 및 개선 방향

### 4-1. 구현한 알고리즘의 장점

보통 알고리즘 문제풀이에서는 global variable로 문제의 제한사항에 명시된 최대치 만큼에 해당되는 크기의 변수를 선언해 사용하는 편이다. 그러나 앞선 수 차례의 시도에서 stack overflow가
나서 런타임 에러를 발생시켰기 때문에 더 compact하게 변수를 사용하고자 하였다. 그래서 입력
을 받은 n, m, q 값에 대응하는 알맞은 크기만큼의 변수를 사용하여 낭비되는 공간을 최소화 하
였다.

또한 앞서 언급한대로 고유값으로 부여된 지역번호값이 너무 큰 범위에 있어 새로 0부터 시작하
는 새로운 key값을 부여하여 graph상에 mapping이 가능하도록 하였다. 그래서 구현을 함에 있
어 불필요한 순차탐색을 최소화할 수 있었다.

Predecessor 값을 갱신하고 이 새로운 dist를 priority queue에 넣는 과정에 있어서, 실제로 손
으로 이를 해결할 땐 이전 값을 지우고 새로운 값(즉, 더 작은 값)으로 갱신한다. 하지만 priority
queue안에 이미 들어있는 값을 지우기가 곤란했다. 

물론 min heap을 예로 들어, 동일한 key값에대해 서로 다른 value 즉 weight값이 들어온다면 더 작은것만 남기고 큰 것은 priority queue 내에서 제거하는 방식으로 직접 구현한다면 가능하겠지만 (아니면 이미 다른 어떤 방법을 사용하여 이를 방지할 수 있을지 모르지만 찾아보지는 않았다.) 그렇게 중복된 값이 priority queue 내에 남아있더라도 이미 tree 안으로 들어온 vertex의 distance 값보다 크기 때문에 결과에 영향을 주지는 않는다.

하지만 while문을 해당 priority queue가 empty가 아닐 때까지 반복하여 돌고있으므로 무의미한
연산이 수행될 여지가 있어 destination이 tree안으로 들어오면 연산을 종료하도록 하였다.


### 4-1. 구현한 알고리즘의 단점

앞서 언급한 indexContainer는 int형 배열 100만개를 정적으로 선언해두고 사용하고 있다. 이는
시간복잡도를 낮추기 위해 공간복잡도를 포기한 선택이었으므로 아쉽다고 생각한다.

### 4-2. 향후 개선 방향

사실 첫 번째로 이 문제를 풀 때 그래프를 만들기 위해 시도한 방법은 map 자료구조를 이용한
방법이었다. Map 자료구조를 이용하면 indexContainer와 같은 배열을 선언하지 않아도 될 뿐더
러 배열처럼 key를 이용하여 value에 접근할 수 있었다. 하지만 시간초과가 나서 이를 배열로 바
꾸고 다시 문제를 풀게 되었는데, 이를 map을 이용하여 구현을 해보고 싶다. 

---

## 5. 기타 (선택)

### 5-1. 구현 및 개발에 있어 특이 사항

위에 언급한 것 처럼 먼저 map 자료구조를 사용해서 구현을 시도하였다. 기존에 알고 있기로는
map 자료구조는 내부적으로 red-black tree로 구현되어 NlogN 의 시간복잡도를 가지며 탐색 및
삽입 삭제 모두 우수한 성능을 갖는것으로 알고 있었다.

그래서 문제에서 지역번호가 고유값을 갖는다고 나와있었기 때문에 map을 이용하여 그래프를 구
현하기 시작했으나 왜 인지 모르게 그 이후에 vector로 구현한 그래프보다 성능이 한참 뒤떨어졌
다.

map에서는 중복된 key값을 허용하지 않기 때문에 내부적으로 그 중복 key값을 찾는 것과 같은
연산이 수행되어서 인지, 아니면 또 다른 부가적인 구현 때문인지 아직 잘 모르겠다. 그래서 map
을 직접 구현해서 다시 한번 시도해 볼 계획이다.