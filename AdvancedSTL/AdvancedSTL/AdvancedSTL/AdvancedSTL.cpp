#include <memory>
#include <iostream>
using namespace std;

struct testStruct
{
	testStruct()
	{
	}

	~testStruct()
	{
		cout << "test dtor" << endl; 
	}
};

int main()
{
	auto sp = make_shared<int>(1729);
	auto sp2 = sp;
	auto sp3 = sp;
	weak_ptr<int> wp(sp);
	auto wp2 = wp, wp3 = wp, wp4 = wp, wp5 = wp;
	sp.reset();
}