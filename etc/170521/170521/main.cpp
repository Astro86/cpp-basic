
#include <iostream>

using namespace std;

/*
Ŭ���� : C++�� ��ü���� ����̴�. ��ü �����̶� ��ü���� �����ؼ� �����Ͽ� �ϼ���
���α׷��� �������� ���α׷��� ����̴�. C++���� ��ü���� ���α׷����� ����
�����Ǵ� ������ Ŭ�����̴�. Ŭ������ ����ü�� ���������� ��������� ���� Ÿ����
���� �� �ִ�. ���� �������� ��� ������ �����ϰ� ���� �Ӹ� �ƴ϶� �Լ���
����� ���� �� �ִ� ����� �����Ѵ�.

Ŭ������ 4���� �Ӽ�
ĸ��ȭ : ���� ������ �� �Լ��� ��� �ϳ��� �������̽��� �����ϴ� �����
���Ѵ�.

����ȭ : �����͸� �ܺηκ��� ���� �� �ִ� ����� �����Ѵ�.
public : Ŭ���� ���� �Ӹ� �ƴ϶� �ܺο� ��� �����ϴ� Ű�����̴�.
protected : Ŭ���� �ܺο����� ������ �Ұ����ϰ� ���� �� ��Ӱ��迡�� �ڽ��� ���ο�����
������ ���ȴ�.
private : Ŭ���� ���ο����� ������ �����ϰ� �ܺ� �� �ڽĿ����� ������ �Ұ����ϴ�.

��Ӽ� : Ŭ������ �θ�� �ڽ��� ���踦 ������ �� �ִ� ����� �����Ѵ�. �̸� ����̶��
�Ѵ�. ����� �ްԵǸ� �ڽ��� �θ��� ����� ����� �� �ְ� �ȴ�.

������ : RTTI(Real Time Type Information) �������� ��Ӱ��迡 �ִ� Ŭ��������
���� ����ȯ�� ������ �Ӽ��� ���Ѵ�.

Ŭ������ ����
class Ŭ������ {}; �� ���·� ������ �ȴ�. ����ü�� ����ϴ�.
Ŭ�������� �̿��ؼ� ������ ������ �� �ִ�.
*/

typedef class CStudent
{
	// ������� ���� �ƹ��͵� �ٿ����� ���� ��� �⺻���� private�̴�.
	// ����ü�� �⺻���� public�̴�.
public:	// ���� �����ڴ� �ѹ� ������� �ٸ��� ���� ������ �� �Ʒ��δ� ��� ����ȴ�.
	int		m_iKor;
	int		m_iEng;
	int		m_iMath;
	int		m_iTotal;
	float	m_fAvg;
	int*	m_pData;

public:
	// �Ϲ� ��������� ������ �� ��ü���� �޸𸮰� �Ҵ�ǰ� ó���� �ȴ�.
	// static ��� ������ �� Ŭ������ �̿��ؼ� ������ ��� ��ü�� �����ϴ�
	// �ϳ��� �޸𸮸� ��������� �ȴ�.
	static int	m_iStaticTest;

public:																			
																				
	// ����Լ� : �� Ŭ������ �̿��ؼ� ������ ��ü�� ����� �� �ִ� �Լ��̴�.
	void Output()
	{
		/*
		this : �ڱ� �ڽſ� ���� �������̴�. ����Լ��� ȣ���Ҷ� Ư�� ��ü��
		�Լ��� .�� �̿��ؼ� ȣ���� �ϰ� �ȴ�. �̷� ��� ���������� this�� ȣ����
		ȣ������ �����͸� ���� ������ش�. �� std1.Output() �Լ��� ȣ���ϸ�
		std1�� ���� �����͸� this �� �ְ� ȣ���� ���ش�. �׷��� ������ this��
		ȣ�����̹Ƿ� ��������� �����Ҷ� �ش� ��ü�� �޸𸮷� �����ϰ� �ȴ�.
		this->m_iKor �� ��� �´µ� this->�� ������ ���̴�.
		*/
		cout << "���� : " << this->m_iKor << endl;
		cout << "���� : " << m_iEng << endl;
	}

	// static ����Լ� : static ����Լ��� �� 1���� �Ҵ�ȴ�. ��� ��ü����
	// �����ؼ� ����ϴ� �Լ��̴�. �׷��� ������ this�� ������ �ȵȴ�.
	// �� �Ϲ� ��������� �̰����� ����� �Ұ����ϴٴ� ���̴�.

	static void StaticFunction()
	{
		// static ��� �Լ� �ȿ����� static ��������� ��� �����ϴ�.
		//m_iKor = 100;
		int	iKor;													
		static int	iEng = 300;
		cout << "Static Function" << endl;
	}

public:
	/*
	Ŭ�������� Ư���� �Լ��� �������ִµ� �����ڿ� �Ҹ����̴�.

	�����ڶ� �� Ŭ������ �̿��ؼ� ��ü�� �����Ҷ� ȣ��Ǵ� �Լ��� ���Ѵ�.
	��ü ������� �ʱ�ȭ�� ������ �Լ��̴�.

	�Ҹ��ڶ� �� Ŭ������ �̿��ؼ� ������ ��ü�� �޸𸮿��� �����ɶ� ȣ��Ǵ�
	�Լ��̴�. ��ü�� �����۾��� �����ϴ�.
	*/
	CStudent()	: // Initializer : ���� ����� ���ÿ� �ʱ�ȭ�� �ؾ��Ҷ� ����Ѵ�.
		m_iKor(100),
		m_iEng(95),
		m_iMath(98)
	{
		m_iMath = 93;
		m_pData = new int;
		*m_pData = 300;
	}

	CStudent(int iKor, int iEng, int iMath)	:
		m_iKor(iKor),
		m_iEng(iEng),
		m_iMath(iMath)
	{
		m_iTotal = iKor + iEng + iMath;
		m_fAvg = m_iTotal / 3.f;

		m_pData = new int;
		*m_pData = 300;
	}

	CStudent(const CStudent & std)						
	{													
		m_iKor = std.m_iKor;							
		m_iEng = std.m_iEng;
		m_iMath = std.m_iMath;							
		m_iTotal = std.m_iTotal;						
		m_fAvg = std.m_fAvg;
		// �޸𸮸� �����ϰ� �ȴ�.
		//m_pData = std.m_pData;						
														
		// �������� : ������ ���� �Ҵ��ϰ� ���� �����Ѵ�.
		m_pData = new int;
		*m_pData = *std.m_pData;
	}

	~CStudent()
	{
		delete	m_pData;
	}
}CSTUDENT, *PCSTUDENT;

// static ��������� �ݵ�� ����ϰڴٰ� �������־�� �Ѵ�.
int	CStudent::m_iStaticTest = 0;						
														
//typedef CStudent	STUDENT;

/*
�Լ������� : �Լ��� �޸� ������ �Ҵ�ǰ� �ȴ�.
�Ϲ� ���� �Լ��� �� 1���� �����ϰ� �Լ��� ��ü�� �Լ��� �������̴�.
*/
void FunctionPointer()
{
	cout << "Function Pointer" << endl;
}

void FuncTest1(int a)
{
	cout << a << endl;
}

void FuncTest2(int a, int b)
{
	cout << a << "\t" << b << endl;
}

int FuncTest3(int a, int b)
{
	return a + b;
}

int main()
{
	CStudent	std1, std2;
	CSTUDENT	std3;

	std1.m_iKor = 100;

	PCSTUDENT	pStudent = &std1;

	pStudent->m_iEng = 90;

	cout << std1.m_iMath << endl;
	cout << std2.m_iMath << endl;
	cout << std3.m_iMath << endl;

	std1.Output();
	std2.Output();
	std3.Output();

	// �Ϲ� �����Լ��� �Լ��� ��ü�� �ش� �Լ��� �޸� �ּ��̴�.
	// �Լ������� �������� : ����Ÿ�� (*������)(����Ÿ��); ���� ���� �����ϴ�.
	void(*pFuncPointer)() = FunctionPointer;

	pFuncPointer();

	void(*pFuncTest1)(int) = FuncTest1;
	pFuncTest1(10);

	void(*pFuncTest2)(int, int) = FuncTest2;
	pFuncTest2(10, 20);

	int(*pFuncTest3)(int, int) = FuncTest3;
	cout << pFuncTest3(10, 20) << endl;

	/*
	����Լ� ������ : ����Լ��� �� 1���� �޸𸮿� �Ҵ�ȴ�.
	�׷��� ����Լ� ���� ��쿡�� this�� ���� �Ǿ�� �ϱ� ������ �ݵ�� ȣ���ڸ�
	������ �־�� �Ѵ�.
	����Ÿ�� ���� : ����Ÿ�� (Ŭ������::*������)(����); �� ���·� �����ȴ�.
	*/
	void(CStudent::*pFunc)() = &CStudent::Output;
	(std1.*pFunc)();

	std1.m_iStaticTest = 100;
	std2.m_iStaticTest = 200;
	std3.m_iStaticTest = 300;
	CStudent::m_iStaticTest = 400;

	cout << std1.m_iStaticTest << endl;
	cout << std2.m_iStaticTest << endl;
	cout << std3.m_iStaticTest << endl;

	CStudent::StaticFunction();

	// static ����Լ��� �Ϲ� �Լ� ������ó�� ����� �����ϴ�.
	void (*pFuncStatic)() = CStudent::StaticFunction;

	pFuncStatic();

	CStudent	std4(10, 20, 30);
	// ���� �����ڸ� ȣ���Ѵ�. ���� �����ڴ� �Ȱ��� Ÿ���� ��ü�� �޾Ƽ�
	// �� ��ü�� ���� ���� �����ϴ� ��ü�� �������ִ� �������̴�.
	// ���� ��Ŀ��� 2���� ����� �ִ�. Deep Copy, Shallow Copy
	// �Ϲ� ���� �����ϴ� ��� ���� �����̴�.
	// �� �Ӹ� �ƴ϶� �޸� �������� ���� �Ҵ��ؾ� �� ��� ���� �����̴�.
	// ��������ڸ� ��������� ���� ��� ����Ʈ ��������ڰ� ȣ��ȴ�.
	// ���� ���縦 �Ѵ�.
	CStudent	std5(std4);

	return 0;
}
