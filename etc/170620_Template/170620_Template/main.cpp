
#include <iostream>

using namespace std;

/*
���ø� : Ÿ���� ���������� �޾ƿ� �� �ִ� ����̴�. ������ Ÿ���� �ƴ� �Ź� ȣ���Ҷ����� �ٸ� Ÿ������
���ǵǵ��� ������� �� �ִ�. �Լ����� ����� �����ϰ� Ŭ�������� ����� �����ϴ�. ��, Ŭ���� ��ü�� ����������,
Ŭ������ ��� �Լ� �ϳ����� �����ϴ�. ���� �������� �����ϴ�.
���� : template <typename ���ϴ��̸�> ���� ���� �����ϴ�.
typename, class ���� �ϳ��� �Ἥ �����Ѵ� . �������� ����Ÿ�Ե� ���� �����ϴ�.
template <typename T1, class T2, typename T3> ó�� �������� �����ϴ�.
*/
template <typename T>
void OutputType()
{
	// typeid �Լ��� �ȿ� ������ Ÿ�������� ���ڿ��� ǥ������ �� �ִ�.
	cout << typeid(T).name() << endl;
}

template <typename T>
class CTest
{
public:
	T	m_Data;
};

int main()
{
	// <Ÿ��> �� �̿��ؼ� T�� �� Ÿ���� �������� �� �ִ�.
	OutputType<int>();
	OutputType<float>();
	OutputType<CTest<int>>();

	return 0;
}
