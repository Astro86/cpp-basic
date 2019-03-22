
#include <iostream>

using namespace std;

#define	NAME_SIZE	32
#define	STUDENT_MAX	10

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
	/*
	������ : ��� ����Ÿ���� ������Ÿ���� ���� �� �ִ�. ������Ÿ���� �̿��Ͽ� ������ ������
	�ش� Ÿ������ ������ ������ �޸� �ּҸ� ������ ������ �ȴ�. �޸� �ּҸ� �˰� �ִٸ�
	�� �ּҿ� �����Ͽ� ���� �����ϰų� ������ ����� �� �ִ�.
	������ ������ �ڱ� �����δ� �ƹ��͵� �� �� ����. �ݵ�� � ������ �޸��ּҸ� �����ְ�
	�� �ּҸ� �����ؾ߸� ���� �� �� �ִ�.
	�����ʹ� �޸� �ּҸ� ������ ���� �Ǳ� ������ Ÿ�Կ� ������� ������ 4byte�̴�.
	�ֳ��ϸ� �޸� �ּ�ü��� 16���� 8�ڸ��� �����ȴ�. �� 16���� 1�ڸ��� 2���� 4�ڸ��̰�
	2���� 1�ڸ��� 1bit�̹Ƿ� 4bit * 8 = 32bit�� �Ǽ� 4byte�̴�.
	���� : ����Ÿ�� *������;���� �ϰԵȴ�.
	��) int iNumber = 100;
	// & �ּҸ� �����Ѵ�.
	int *pNumber = &iNumber;
	*/

	// �������� 64��Ʈ������ �ϰ� �Ǹ� 8����Ʈ�� ���´�.
	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;

	int	iNumber = 100;
	int	*pNumber = &iNumber;

	// ������ : �����ͺ����� � ������ �޸� �ּҸ� ������� ��� �ش� �ּҿ� �����Ͽ�
	// ���� �ٲ� �� �ִ� ����� ���Ѵ�. ������ ���� �տ� *�� �ٿ��� �����Ѵ�.
	// �Ʒ��� pNumber�տ� *�� �ٿ����Ƿ� pNumber�� ����Ű�� ����� ���� �ǹ��Ѵ�.
	// pNumber�� iNumber�� �ּҸ� ���� �����Ƿ� iNumber�� ����Ű�� *pNumber��
	// iNumber�� ���� �ǹ��Ѵ�.
	*pNumber = 200;

	cout << "iNumber : " << iNumber << endl;
	cout << "iNumber�� �ּ� : " << &iNumber << endl;
	cout << "pNumber : " << pNumber << endl;
	cout << "pNumber�� �ּ� : " << &pNumber << endl;

	// �������� const
	// const Ű����� ����Ÿ�� ���̳� ����Ÿ�� �ڿ� �ٿ��� �� �ִ�.
	const int *cpNumber = &iNumber;

	// cpNumber�� const�� ���� �տ� �ٿ��־��� ������ ����Ű�� ����� ����
	// ������ �� ����. ������ ����Ű�� ��� ��ü�� �����ϴ� ���� �����ϴ�.
	//*cpNumber = 300;
	int		iNumber1 = 500;
	cpNumber = &iNumber1;

	cout << *cpNumber << endl;

	// const �� ����Ÿ�� �ڿ� �ٿ��ְ� �Ǹ� ����Ű�� ����� ������ �� ����.
	// ����Ű�� ����� ���� ������ �����ϴ�.
	int* const pcNumber = &iNumber;

	*pcNumber = 1234;

	//pcNumber = &iNumber1;

	cout << iNumber << endl;

	// �Ѵ� �ٿ��ָ� 2���� Ư¡�� ��� ���� �ȴ�. �� ����Ű�� ��� ������ �� ����
	// ����Ű�� ����� ���� ������ �� ����.
	const int* const cpcNumber = &iNumber;

	//*cpcNumber = 11223;
	//cpcNumber = &iNumber1;
	//const int	iAttack = 0x1;

	// "" ���ڿ��� ���� �Ǹ� const char* �̴�. ���ڿ� ������� �����ϴ� �޸� ������
	// �׽�Ʈ <== ���ڿ��� ����ǰ� �� �ּҸ� ���Ϲ޾Ƽ� �����صд�.
	// pText�� �� ���ڿ� ����� �ּҸ� ���Եǰ� �� �ּҸ� �����Ͽ� ����ϰ� �ȴ�.
	// const�̱� ������ ���� ������ �Ұ����ϴ�.
	char*	pText = "�׽�Ʈ";

	cout << pText << endl;
	cout << (int*)pText << endl;

			//���� : (int*)�� �ٿ��� ��������ȯ �ؼ� ��µ� ���� pText�� �ּҰ�??

	// ��������� Ÿ�Ե鵵 ����Ÿ���̴�. �׷��Ƿ� ������ ������ ������ �� �ִ�.
	_tagStudent		tStudent = {};

	_tagStudent	*pStudent = &tStudent;

	cout << "_tagStudent : " << sizeof(pStudent) << endl;

	(*pStudent).iKor = 100;
	// ����ü �����͸� �̿��Ͽ� ����Ű�� ����� ���� �����Ҷ��� ���� ����� �Ʒ��� ��� ���
	// ����� �� �ִ�.
	pStudent->iKor = 200;

	cout << tStudent.iKor << endl;
	cout << "tStudent�� �ּ� : " << &tStudent << endl;
	cout << "pStudent : " << pStudent << endl;
	cout << "pStudent�� �ּ� : " << &pStudent << endl;

	// �������� �迭�� ����
	// �߿�) �迭���� �����ʹ�. �迭�� ���ӵ� �޸� ��Ͽ� �Ҵ�ȴ�.
	// �迭���� �ش� �迭�� ���� �޸� �ּҸ� ������ �ִ�.
	
	int	iArray[10] = {};
	// �迭���� �迭�� ���� �޸� �ּ��̹Ƿ� &�� �ٿ����� �ʾƵ� �ּ��̱� ������
	// ������ ������ ������ �����ϴ�.
	int	*pArray = iArray;
	// ++�� ���ְ� �Ǹ� iArray[1] �� �޸� �ּҸ� ���Եȴ�.
	pArray++;
	// �׷��Ƿ� ���⼭ 1�� �ε����� iArray�������� 2���ε����� �ȴ�.
	pArray[1] = 1234;
	//�����Ͱ� �迭�� ����Ű�� �ε����� �̿��ؼ� �ش� �迭�� ������ �����ϴ�
			//���� : pArray �� iArray �迭�� �����ּҸ� ���� ������ �����ε�
			//		������ ������ pArray[1] �� ǥ���� �ǹ̰� ��������?

	// ���� �ε����� �����ϴ� �ǹ̴� �Ʒ�ó�� ������ �Ͼ��.
	cout <<"pArray : " <<pArray << endl;
	cout << "pArray[0] : " << pArray[0] << endl; //pArray�� ������ �������� �迭�� �ƴѵ� pArray[0]���� 0�� ���ִ� ���� ( �����Ⱚ�� �ƴ϶�) 
	cout << "pArray[1] : "<<pArray[1] << endl;
	cout << "*(pArray + 1) : " <<*(pArray + 1) << endl;//pArray�� iArray[0]�� �ּҰ�. �� �ּҰ��� 4��(intŸ�� �̱⿡) ���� �ּҿ� �ش��ϴ� ���� ȣ��??
													   //�ᱹ iArray[1]�� ���� ȣ��?
	cout << "*pArray + 1 : "<<*pArray + 1 << endl;	//pArray�� ������ = 0 ���� 0+1 = 1
	cout << "iArray[1] : "<<iArray[1] << endl;		//iArray�� 1�� �ε����� = pArray[0]
	cout << "iArray[2] : "<<iArray[2] << endl;

	// �������� ���� : +, -���길 �����Ѵ�.
	// ++�� �� ��� 1�����ε� �����ͺ����� ++�� �ϰ� �ȴٸ� �ܼ��� 1 ������ �ƴϴ�.
	// �����ʹ� �޸� �ּҸ� ���� �ִ� �����̴�.
	// �ش� ������Ÿ���� ũ�⸸ŭ �����Ѵ�.
	// ���� int* ��� 4��ŭ �����ϰ� �Ǵ°��̴�.
	
	cout << "pArray : " << pArray << endl;
	cout << "pArray + 1 : " << pArray + 1 << endl;

	char	str[10] = {};

	char	*pStr = str;

	cout << "(int*)pStr : "<<(int*)pStr << endl;
	cout << "(int*)(pStr + 1) : " << (int*)(pStr + 1) << endl;

	_tagStudent	tStdArr[STUDENT_MAX] = {};
	_tagStudent	*pStdArr = tStdArr;

	cout << "pStdArr : " <<pStdArr << endl;
	cout << "pStdArr + 1 : " <<pStdArr + 1 << endl;

	return 0;
}