#include<iostream>

using namespace std;


/*A Lmax(A a, A b)
{
	return a > b ? a : b;
	//return a.operator>(b)?a:b;
}*/
template<class T2,class T1,class T3> T2 Lmax(T2 a, T1 b,T3 )
{
	return a > b ? a : b;
}

//class A
//{
//public:
//	bool operator>(A&)
//	{
//		return true;
//	}
//	int value = 2;
//};
//ostream & operator<<(ostream & o, A& a)
//{
//	cout << "cout A类的变量" << endl;
//	return o;
//}

int Lmax(int a, int b)
{
	return a > b ? a : b;
}

void Lswap(double& a, double &b)
{
	double tem = a;
	a = b;
	b = tem;
}
void Lswap(int& a, int& b)
{
	int tem = a;
	a = b;
	b = tem;
}
template<class T>void Lswap(T& a, T&b)
{
	T tem = a;
	a = b;
	b = tem;
}
//void Lswap(A&a, A&b)
//{
//	A tem = a;
//	a.operator=(b);
//	b.operator=(tem);
//}
class A
{
public:
	int value = 0;
	char*p;
	A(int v)
	{
		p = new char[100];
		value = v;
		cout << "构造函数" << endl;
	}
	A(const A & other)
	{
		p = new char[200];
		value = other.value;
		cout << "拷贝构造" << endl;
	}

	A & operator=(const A& other)
	{
		delete p;
		p = new char[100];
		value = other.value;
		return *this;
	}
	void swap(A&b)
	{
		auto tem = p;
		p = b.p;
		b.p = tem;

		auto tem2 = value;
		value = b.value;
		b.value=tem2;
	}

	~A()
	{
		cout << "析构函数" << endl;
		delete p;
	}
};
int main()
{
	int x1 = 2, x2 = 5;
	double d1 = 2.3, d2 = 4.4;
	A a(25), b(31);
	a.swap(b);
	Lswap(a, b);
	cout <<a.value<<"  "<<b.value<< endl;
	//显示推导
	Lswap<int>(x1, x2);
	cout <<x1<<x2 << endl;
	//显示指定模板，必须使用模板推导的函数
	//cout << Lmax<>(x1, x2) << endl;
	
}
	
