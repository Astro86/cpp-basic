
#include <iostream>

using namespace std;

#include "Dijkstra.h"

int main()
{
	CDijkstra<const char*>	subway;

	subway.AddVertex("사당");
	subway.AddVertex("강남");
	subway.AddVertex("신논현");
	subway.AddVertex("교대");
	subway.AddVertex("역삼");
	subway.AddVertex("서초");
	subway.AddVertex("고속터미널");

	subway.AddEdge("사당", "서초", 30);
	subway.AddEdge("서초", "교대", 30);
	subway.AddEdge("교대", "강남", 40);
	subway.AddEdge("교대", "고속터미널", 50);
	subway.AddEdge("강남", "신논현", 50);
	subway.AddEdge("강남", "역삼", 30);
	subway.AddEdge("고속터미널", "신논현", 40);

	CLinkedList<const char*>	output;

	subway.Find(output, "사당", "신논현");

	if (!output.empty())
	{
		CLinkedList<const char*>::iterator	iter;
		CLinkedList<const char*>::iterator	iterEnd = output.end();

		for (iter = output.begin(); iter != iterEnd; ++iter)
		{
			cout << *iter << " -> ";
		}

		cout << endl;
	}

	return 0;
}
