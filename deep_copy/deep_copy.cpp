#include<iostream>
using namespace std;
class student
{
public:
	student()      
	{
		cout << "������" << endl;
	}
	student(const student& t)
	{
		this->sno = t.sno;
		this->age = t.age;
	}
	~student()
	{
		cout << "������" << endl;
	}
private:
	int sno;
	int age;    
};
int main()
{
	student t;
	student t2(t);
}