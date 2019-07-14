
#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
	CQueue<int>	queue;

	for (int i = 0; i < 10; ++i)
	{
		queue.push(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << queue.pop() << endl;
	}

	CCircleQueue<int, 200>	queue1;

	for (int i = 0; i < 200; ++i)
	{
		queue1.push(i);
	}

	for (int i = 0; i < 50; ++i)
	{
		cout << queue1.pop() << endl;
	}

	for (int i = 0; i < 100; ++i)
	{
		queue1.push(i);
	}

	cout << "Size : " << queue1.size() << endl;

	for (int i = 0; i < 200; ++i)
	{
		cout << queue1.pop() << endl;
	}

	return 0;
}
