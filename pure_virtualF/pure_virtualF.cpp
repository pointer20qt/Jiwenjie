#include<iostream>

using namespace std;

class A
{
public:
	virtual void fun()=0;
	
	virtual void func()
	{
		cout << "AµÄfunc" << endl;
	}
};

class B:public A
{
public:
	
	void fun()
	{
		cout << "BµÄfun" << endl;
	}
};
int main()
{
	A *p=new B;
	p->fun();

	return 0;
}