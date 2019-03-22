
#include <iostream>

using namespace std;

// #define : ��ó�����̴�. define �̸��� ����ϸ� �̸� �ڿ� �մ� ���̳� �ڵ带
// �����ϴ� ����̴�.
#define	NAME_SIZE	32

/*
����ü�� ��������� Ÿ���� ������� �� �ִ� ����̴�. �پ��� �����ִ� �������� ��Ƽ�
ĸ��ȭ �ϰ� ����ü���� �̿��ؼ� ����ü ������ �����Ͽ� ������� ����� �� �ְ� ���ش�.
����ü�� ũ��� ���ũ���� �� ���̴�.
*/

struct _tagStudent

{
	char	strName[NAME_SIZE];
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

int main()
{
	cout << sizeof(_tagStudent) << endl;
	// ����ü���� �ش� ����ü ���� Ÿ���̴�. �׷��� ������ ����ü������ ����ü ������
	// �����ؼ� ����Ѵ�.
	_tagStudent	tStd;

	tStd.iKor = 10;

	// ���ڿ� ���� : strcpy_s(src, dest) �� ���·� ������ �Լ��� �̿��Ѵ�.
	// dest�� src�� �����Ѵ�.
	strcpy_s(tStd.strName, "ö��");
	
		//���� : tStd.strName = "ö��" �� ���� �ۼ������ʰ� ī�Ǹ� �ϴ� ����
		//�迭�� ���Ͱ��� �ִ°��� �Ұ����ϴ�. ���������ʴ� �����
		//���� ö�� �� �� 4����Ʈ �̱⶧���� ������ �ش��ϴ� �ƽ�Ű�ڵ尪��
		//�迭�� ���ʴ�� ����ְԲ� �ϱ�����.

	// strlen : ���ڿ��� ���̸� �����ִ� �Լ��̴�.
	// �ѱ��� ���� 1���� 2byte�� �����Ѵ�. ����, ���ڸ� 1byte�̴�.
	cout << "Length : " << strlen(tStd.strName) << endl;

	// strcmp : ���ڿ��� ���ϴ� �Լ��̴�. ���� ��� 0�� ��ȯ�Ѵ�.
	cout << "�̸� ö��? : " << strcmp(tStd.strName, "ö��") << endl;

	cout << tStd.strName << endl;

	return 0;
}