
#include <iostream>

using namespace std;

// �Լ� �����ε� : �Լ� �̸��� ������ ���ڰ� �ٸ����� ���Ѵ�.
// ���� �̸����� �ٸ� ������ ���� �Լ��� ������� �� ����Ѵ�.
// ����Ÿ���� �Լ� �����ε��� ������ ���� �ʴ´�.
void Output()
{
	cout << "Output Blank" << endl;
}

void Output(int iNumber)
{
	cout << "Output(int iNumber) : "<<iNumber << endl;
}

void Output(float fNumber)
{
	cout << "Output(float fNumber) : "<<fNumber << endl;
}

void Output(int iNumber, int iNumber1)
{
	cout << "Output(int iNumber, int iNumber1) : "<<iNumber << "\t" << iNumber1 << endl;
}

void Default(int iNum = 100)
{
	cout << "Default : "<<iNum << endl;
}

int main()
{
	Output();
	Output(10);
	Output(3.14f);
	Output(10, 20);

	Default();
	Default(1234);		


	// ���� �Ҵ� : �޸� �Ҵ��� ���� ���ϴ� ������ �������� �Ҵ�
	// �Ѵ�. �Ϲ����� ���������� �ش� �ڵ������ �����帧�� �̵�
	// �Ҷ� �޸𸮿� �Ҵ�ȴ�. ���������� ���α׷��� ���۵ɶ�
	// �Ҵ�ȴ�. ������ �����Ҵ��� �ϸ� ���� ���ϴ� ������ �޸�
	// �� �Ҵ��� �� �ִ�. �����Ҵ��� �޸𸮴� ���� �Ҵ�ȴ�.
	// new Ű���带 �̿��ؼ� �޸𸮸� �����Ҵ� �� �� �ִ�.
	// ���� �����ϱ� ����� �Ʒ�ó�� �����Ҵ��� �ϸ� pNumber��
	// �޸𸮸� �Ҵ��ϴ� ������ �����Ѵ�. ������ �� �ǹ̴� �ƴϴ�.
	// new int�� �ϰ� �Ǵ� ���� �޸� �������� ��򰡿� int��
	// ũ�⸸ŭ(4byte) �Ҵ��� �ϰ� �Ҵ�� �޸� �ּҸ� �����Ѵ�.
	// �׷��� �Ǹ� int*������ pNumber�� �� �ּҸ� �����ְ�
	// �ּҸ� �˰������Ƿ� ���� �Ҵ�� �޸𸮰����� ���ϴ� ����
	// �ְ� �� �� �ִ�.
	int*	pNumber = new int;
	*pNumber = 300;		//���� : *pNumber�� �ǹ��ϴ°� 
						//pNumber�� ����Ű�� �ּ��� 4����Ʈ ������ 300�̶�� ���빰�� �����Ѵٴ� �Ҹ�?
	cout << *pNumber << endl;

	// ���� �����Ҵ��� �ϸ� �ݵ�� delete Ű���带 �̿��ؼ�
	// �޸𸮸� ������ �־�� �Ѵ�. �������� ������ �޸𸮰�
	// ���� �Ǵµ� �̷� ������ �޸� Leak�̶�� �Ѵ�.
	delete	pNumber;

	// ���� �迭 : �������� �迭�� �����ϴ� ���̴�.
	int		iNum = 300;
	int*	pArray = new int[iNum];
	int		iArray[300];
	delete[]	pArray;

	return 0;
}
