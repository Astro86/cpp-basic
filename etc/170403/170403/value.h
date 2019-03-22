
// #pragma once : �� ��������� �� 1���� ���Խ�Ű�ڴٴ� �ǹ��̴�.
// value ����� ���������� ���Ǵ� ������� ��Ƽ� ������ ���� �뵵��
// ����Ѵ�.
#pragma once

#include <iostream>

using namespace std;

// ��� �л��� �ִ�ġ�� �����д�.
#define	STUDENT_MAX		10
#define	NAME_SIZE		32

// typedef : Ÿ���� �������Ѵ�.
// ��) typedef int MyInt; ���ְ� �Ǹ� 
// MyInt  i = 0; �̷��� int������ �������� �� �ִ�.
typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
	char	cScore;
}STUDENT, *PSTUDENT;
// _tagStudent ��ſ� STUDENT �� Ÿ���� �� �� �ִ�.
// PSTUDENT�� �տ� *�� �پ� �ֱ� ������ ������Ÿ�� ������ ������ �� �ִ�.

// MENU
enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

// ������Ͽ� �Լ��� �����κб��� ���� ������ֱ� ���ؼ��� �Ϲ��Լ���
// ó���ϴ°��� �Ұ����ϴ�.
// �Լ� �տ� static�� �ٿ��ְ� �Ǹ� �� �Լ��� ������ cpp����
// ���� �ٸ� �Լ��� �ν��� �ȴ�. �׷��� ������ �ߺ������� �ƴ�
// ���� �ϳ��� ������ ������ �ǰԵȴ�.
static int InputInt()
{
	int	iInput;
	cin >> iInput;

	// �Է¿� �������� ��� true�� �����Ѵ�.
	if (cin.fail())
	{
		// �Է��� ������Ʈ�� ��� �ʱ�ȭ�Ѵ�.
		cin.clear();
		// \n�� ã�Ƴ��� �Է¹��۸� ����ش�.
		cin.ignore(1024, '\n');
		return INT_MAX;	// �Է� ���н� Ư������ INT_MAX�� ��Ƶξ���.
	}

	return iInput;
}

static bool InputString(char* pText, int iCount)
{
	cin.getline(pText, iCount);

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		pText[0] = 0;
		return false;
	}

	return true;
}