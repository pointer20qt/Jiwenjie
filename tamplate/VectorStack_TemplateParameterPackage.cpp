#include<iostream>
#include<vector>

using namespace std;




//vector实现栈
template<class T> class L_stack
{
	std::vector<T> arr;
public:
	void push(T&&obj)
	{
		arr.push_back(obj);
	}
	void pop()
	{
		arr.pop_back(obj);
	}
	T & top()
	{
		return arr.back();
	}
	size_t size()
	{
		return arr.size();
	}
	bool empty()
	{
		return arr.empty();
	}
};

//模板参数包 拆包
void Lprint()
{
	cout <<"拆包结束"<< endl;
}
/*void Lprint(int f, const char* d)
{
	cout << f << endl;
	Lprint(d);
}
void Lprint(double f, int d1, const char*d2)
{
	cout << f << endl;
	Lprint(d1,d2);
}
void Lprint(int f, double d1, int d2, const char* d3)
{
	cout << f << endl;
	Lprint(d1,d2,d3);
}*/
template<class T, class...args>void Lprint(T f,args... d)
{
	cout << f << endl;
	Lprint(d...);
}
int main()
{
	L_stack<int> l;
	l.push(5);
	l.push(6);
	l.push(7);

	Lprint<int>(1,2,3,"123");
	cout << l.top() << endl;
}
	
