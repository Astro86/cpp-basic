
#include "Core.h"

/*
������Ʈ �̷�ã��
*/
int main()
{
	// Core �ʱ�ȭ
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	CCore::GetInst()->Run();

	return 0;
}