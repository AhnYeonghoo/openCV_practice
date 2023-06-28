#include "Resource.hpp"
#include "AutoPtr.hpp"
using namespace std;

// RAII��Ģ �ڱⰡ ������ �����ʹ� �ڱⰡ å������ �Ҹ���Ѿ� �Ѵ�.

void doSomething()
{
	//Resource* res = new Resource; // dull pointer
	AutoPtr<Resource> res = new Resource; // smartPointer
	AutoPtr<Resource> res2(new Resource);
	
	
	return;
}

int main_example15_1()
{
	doSomething();

	{
		AutoPtr<Resource> res1(new Resource);
		AutoPtr<Resource> res2;
		
		cout << std::boolalpha;
		cout << res1.m_ptr << endl;
		cout << res2.m_ptr << endl;

		res2 = res1;

		cout << res1.m_ptr << endl;
		cout << res2.m_ptr << endl;
	}

	return 0;
}