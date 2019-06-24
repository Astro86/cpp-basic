
#include "Graph.h"

int main()
{
	CGraph<int>	graph;

	for (int i = 0; i < 15; ++i)
	{
		graph.AddVertex(i + 1);
	}

	graph.AddEdge(1, 2);
	graph.AddEdge(1, 3);

	graph.AddEdge(2, 4);
	graph.AddEdge(2, 5);

	graph.AddEdge(3, 6);
	graph.AddEdge(3, 7);

	graph.AddEdge(4, 8);
	graph.AddEdge(4, 9);

	graph.AddEdge(5, 10);
	graph.AddEdge(5, 11);

	graph.AddEdge(6, 12);
	graph.AddEdge(6, 13);

	graph.AddEdge(7, 14);
	graph.AddEdge(7, 15);

	graph.BFS(1);

	graph.DFS(1);

	return 0;
}
