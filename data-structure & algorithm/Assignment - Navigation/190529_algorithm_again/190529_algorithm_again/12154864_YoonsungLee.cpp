#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
using namespace std;

// weight의 값이 동일한 경우 지역번호가 더 작은 정점을 우선적으로 계산하고자 아래처럼 comparator를 구현하였다.
struct PQcomparator
{
	bool operator()(pair<int, int> candi1, pair<int, int> candi2) {
		if (candi1.first != candi2.first)
			return candi1.first > candi2.first;
		else
			return candi1.second > candi2.second;
	}
};

// <key, name, 침수여부>  순서
vector<tuple<int, string, bool>> vertex_info;

// <source -> <destination, length>> 순서
vector<vector<pair<int, int>>> graph;

// 지역번호의 범위가 100000~999999 의 범위 내에 있기 때문에
// 이를 조금 더 간편하게 불필요한 공간의 낭비없이 사용하고자
// 지역번호와 대응되는 인덱스 값을 저장하여 최초 입력받은
// vertex 갯수 만큼의 새로운 인덱스를 사용하고자
// indexContainer라는 배열을 사용하였다.
// 즉, 0부터 시작하는 새로운 key값을 사용하였다.
int indexContainer[1000000];
int n, m, q;

// predecessor를 추적하는 함수이다. cameFrom 벡터를 사용하여
// 최초 시작점의 predessor 값을 자기 자신으로 넣었기 때문에
// predecessor가 자기 자신이 되는 vertex 까지 반복문을 돌며 찾아 올라간다.
void searchPath(vector<int>& cameFrom, int dest)
{
	// 뒤에서부터 찾아 들어가는 것이기 때문에 개념상 stack을 사용하는것이
	// 적절할 수 있으나, 출력의 편의성을 고려해서 벡터 자료구조를 사용하였다.
	vector<int> chaser = {};
	// destination에 해당하는 키값을 before로 받아온다.
	int before = indexContainer[dest];
	// predecessor가 자기 자신이라면 before는 source까지 타고들어온 것이다.
	while (before != cameFrom[before])
	{
		chaser.push_back(before);
		before = cameFrom[before];
	}
	// before 변수가 source까지 온 경우 while문에서 조건에 걸리지 않기 때문에
	// 한번 더 추가해줘서 source까지 chaser 벡터에 넣어주었다.
	chaser.push_back(before);

	// 그 벡터를 위에서부터 아래로(스택의 pop 대신) 출력하였다.
	for (int i = (chaser.size() - 1); i >= 0; --i)
		cout << get<0>(vertex_info[chaser[i]]) << " ";
	cout << endl;
}

void theGreatDijkstra(char type, int src, int dest)
{
	// dist			: 출발지에서 출발지 외의 vertex 까지 최단 경로를 저장하는 벡터
	// cameFrom		: decreaseKey()가 수행될 때 predecessor 를 담아두는 벡터
	vector<int> dist, cameFrom;

	// 그 벡터들을 resize 하여 앞서 지정해 준 새로운 key값을 인덱스로 사용할 수 있게
	// 구현하였다.
	// dist의 경우 무한대 값으로 init 해주고 알고리즘을 수행하는데, 충분히 큰 값으로 
	// 무한대를 표현하였다.
	dist.resize(n + 1, 1e9);

	// cameFrom의 경우 predecessor의 키 값이 쓰여질 것이기 때문에 앞서 할당한 새로운 key값은
	// 음수로 내려갈 수 없다. 따라서 -1로 init 하였다.
	cameFrom.resize(n + 1, -1);

	// 다익스트라 알고리즘을 구현할 때 fringe 에서의 최단 edge를 뽑아낼 
	// 우선순위 큐 이다.
	// 그래프 상에서 pair 쌍으로 구현이 되어 있어서 아래처럼 인자를 넣어주었다.
	// 추가적으로 comparator 를 직접 정의하여 문제의 요구사항중,
	// "최단거리가 동일한 후보정점이 2개 이상 존재한다면, 지역번호가 더 작은 정점(높은 우선순위)을 우선적으로 계산한다."
	// 에 대응하였다.
	priority_queue<pair<int, int>, vector<pair<int, int>>, PQcomparator> PQ;

	// inTree는 키값이 트리 안에 들어와 있는지를 판단하는 벡터다.
	// 최초 false로 초기화 되어있으며, 트리 안에 들어온 경우 해당
	// 인덱스를 true 로 바꿔준다.
	vector<bool> inTree;
	inTree.resize(n + 1, false);

	// trace는 위의 inTree 벡터를 배열처럼 쓰기 때문에 true에 해당되는
	// 키값의 갯수를 세고자 전체 탐색을 하면 퍼포먼스가 상대적으로 저하될 것을
	// 생각해서 탐색보다는 counting 변수를 두고 하나씩 올리고자
	// 아래 treeSetCount 라는 변수를 두었다.
	int treeSetCount = 0;
	
	// 최초 시작점(src)을 우선순위 큐에 넣어준다.
	// 시작점은 dist를 0으로 주고, predecessor에도 자기 자신을 넣어준다.
	PQ.push({ 0, src });
	dist[indexContainer[src]] = 0;
	cameFrom[indexContainer[src]] = indexContainer[src];

	// 우선순위 큐가 empty일 때까지 반복하여 알고리즘을 수행한다.
	while (!PQ.empty())
	{
		// 우선순위가 가장 높은 즉, 가장 가까운 거리에 있는 vertex를 찾고자
		// weight 값이 가장 작은 key를 PQ 자료구조를 이용해서 뽑아낸다.
		int d = PQ.top().first;
		int now = PQ.top().second;
		PQ.pop();
		
		// Tree 안에 중복된 값이 들어갈 수 있다. 현재 카운팅만 해주고 있기 때문에
		// 트리 안에 있는지 체크해주는 inTree 벡터상에서 해당 키에 대응되는 값이
		// false 즉, 트리 안에 없는 key값만 트리로 넣어준다.
		if (!inTree[indexContainer[now]])
		{
			inTree[indexContainer[now]] = true;
			++treeSetCount;
		}

		// 현재 위치가 입력시 받은 종료점과 일치한다면 알고리즘을 더이상 수행하지 않아도 된다.
		// tree set 안에 들어온 vertex간의 distance 정보는 최단 거리임이 보장되기 때문이다.
		// 불필요한 수행으로 발생할 수 있는 퍼포먼스 저하를 방지하고자
		// 원하는 결과를 얻었으니 while문에서 빠져나오도록 구현하였다.
		if (now == dest)
			break;

		// 그래프상 하나의 노드(now)로부터 연결된 모든 다른 노드들을 돌며 적절한 후보들을 찾는다.
		for (int i = 0; i < graph[indexContainer[now]].size(); ++i)
		{			
			// now vertex에 연결된 다른 버텍스를 얻어온다.
			int next = get<0>(vertex_info[graph[indexContainer[now]][i].first]);
			int nextd = graph[indexContainer[now]][i].second;

			// 얻어온 vertex가 tree set 안에 있지 않고, 침수지역이 아니며,
			// now vertex로 부터 next vertex 까지의 거리 d를 합한 값이
			// next vertex에 셋팅된 distance 값 보다 작은 경우 
			// 이를 갱신해주고, next의 predecessor를 now로 지정해주고, 우선순위 큐에 넣어준다.
			if (!inTree[indexContainer[next]]
				&& !get<2>(vertex_info[indexContainer[next]])
				&& dist[indexContainer[next]] > dist[indexContainer[now]] + nextd)
			{
				dist[indexContainer[next]] = dist[indexContainer[now]] + nextd;
				cameFrom[indexContainer[next]] = indexContainer[now];
				PQ.push({dist[indexContainer[next]] , next});
			}
		}
	}

	// dist값을 최초 1e9 로 설정하였다. 따라서 문제의 요구사항인 1e6을 넘는 경우
	// None 으로 출력하는데에 문제가 없다. 
	if (dist[indexContainer[dest]] > 1e6)
		cout << "None" << endl;
	else
	{
		// 문제에서 요구한대로, 타입이 A인 경우 아래처럼 출력해준다.
		if (type == 'A')
		{
			cout << treeSetCount << " " << dist[indexContainer[dest]] << " "
				<< get<1>(vertex_info[indexContainer[src]]) << " " << get<1>(vertex_info[indexContainer[dest]]) << endl;
		}
		// 문제에서 요구한대로, 타입이 B인 경우 아래처럼 출력해준다.
		else
		{
			cout << treeSetCount << " ";
			// predecessor 값을 추적하기 위해 아래와 같은 함수를 만들었다.
			searchPath(cameFrom, dest);
		}
	}
}


int main()
{
	// 성능 개선을 위해 sync를 풀었다.
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	// 입력을 받는다.
	cin >> n >> m >> q;
	
	// graph를 벡터로 구현하였으므로 불필요한 크기만큼 정적으로 선언하지 않고
	// 그래프의 key값은 입력받은 vertex의 갯수인 n을 초과할 수 없기 때문에
	// 아래와 같이 resize 해 주었다. 하나를 추가적으로 더해서(n+1) 혹시 모를 예외에 대비하고자 하였다.
	graph.resize(n + 1, vector<pair<int, int>>());

	// vertex 정보에 대해 입력을 받는다.
	for (int i = 0; i < n; ++i)
	{
		int vertex_num = 0;
		string vertex_name = "";
		bool die = false;

		cin >> vertex_num >> vertex_name >> die;

		vertex_info.push_back({ vertex_num, vertex_name, die });

		// indexContainer에 지역번호와 1:1로 대응되는 작은 정수값을 부여한다.
		indexContainer[vertex_num] = i;
	}

	// edge 간의 정보를 입력받고 그래프를 생성한다.
	for (int i = 0; i < m; ++i)
	{
		int src = 0, dest = 0, length = 0;
		cin >> src >> dest >> length;
		// 지역번호에 대응되는 새로운 key로 그래프를 생성한다.
		int idxOne = indexContainer[src];
		int idxTwo = indexContainer[dest];
		
		// 양방향 그래프기 때문에 src와 dest를 바꿔 각각 엣지를 연결해준다.
		// 앞서 graph vector를 resize 해 주었기 때문에 이렇게 할당하여도 
		// NULL pointer exception이 발생하지 않는다.
		graph[idxOne].push_back({ idxTwo, length });
		graph[idxTwo].push_back({ idxOne, length });
	}

	// 다익스트라 알고리즘을 수행하여 최단거리 및 최단 경로를 구한다.
	for (int i = 0; i < q; ++i)
	{
		char type = 0;
		int src = 0, dest = 0;
		cin >> type >> src >> dest;

		// 침수지에서의 출발 or 종료는 무의미하기 때문에
		// 알고리즘에 들어가지 않고 차단하였다.
		if (get<2>(vertex_info[indexContainer[src]])
			|| get<2>(vertex_info[indexContainer[dest]]))
			cout << "None" << endl;
		// 침수지에서의 출발 or 종료가 아닌 경우 알고리즘을 수행한다.
		else
			theGreatDijkstra(type, src, dest);
	}
	return 0;
}