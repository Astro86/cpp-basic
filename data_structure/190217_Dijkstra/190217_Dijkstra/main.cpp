
#include <iostream>

using namespace std;

#include "Dijkstra.h"

int main()
{
	CDijkstra<const char*>	subway;

	subway.AddVertex("���");
	subway.AddVertex("����");
	subway.AddVertex("�ų���");
	subway.AddVertex("����");
	subway.AddVertex("����");
	subway.AddVertex("����");
	subway.AddVertex("����͹̳�");

	subway.AddEdge("���", "����", 30);
	subway.AddEdge("����", "����", 30);
	subway.AddEdge("����", "����", 40);
	subway.AddEdge("����", "����͹̳�", 50);
	subway.AddEdge("����", "�ų���", 50);
	subway.AddEdge("����", "����", 30);
	subway.AddEdge("����͹̳�", "�ų���", 40);

	CLinkedList<const char*>	output;

	subway.Find(output, "���", "�ų���");

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
