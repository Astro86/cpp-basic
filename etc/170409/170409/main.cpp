
#include "Core.h"

int main()
{
	int		iNumber[25] = {};

	// 초기화한다. 실패시 종료한다.
	if (!Init(iNumber))
		return 0;

	Run(iNumber);

	return 0;
}