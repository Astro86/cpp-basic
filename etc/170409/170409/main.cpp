
#include "Core.h"

int main()
{
	int		iNumber[25] = {};

	// �ʱ�ȭ�Ѵ�. ���н� �����Ѵ�.
	if (!Init(iNumber))
		return 0;

	Run(iNumber);

	return 0;
}