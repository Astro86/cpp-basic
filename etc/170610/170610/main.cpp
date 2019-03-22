
#include "Core.h"

/*
프로젝트 미로찾기
*/
int main()
{
	// Core 초기화
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	CCore::GetInst()->Run();

	return 0;
}