#include<iostream>
using namespace std;

typedef int i;
using i = int;

typedef void(*FP) (int, const std::string&);
using FP = void(*) (int, const std::string&);


class student
{
	int age = 1;
public:
	int getAge()
	{
		return age;
	}
	student()
	{
		cout << "����" << endl;
	}
	~student()
	{
		cout << "����" << endl;
	}
	friend class teacher;
	
};

class teacher
{
public:
	void printAge(student&s)
	{
		cout << s.age << endl;
	}
	teacher()
	{
		cout << "������" << endl;
	}
	~teacher()
	{
		cout << "������" << endl;
	}
};
int main()
{
	student s;
	teacher t;
	t.printAge(s);
	
	
}