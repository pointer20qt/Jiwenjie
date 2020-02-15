#include<iostream>
#include<vector>
#include<string>
#include<Initializer_List>
#define NDEBUG
#include<assert.h>
using namespace std;

static_assert (sizeof(int)!= 32, "Inappropriate int size");

using namespace std;
class principal{
	string name;
public:
	principal(string sname){
		this->name = sname;
	}
	~principal(){

	}
};

class school{
	std::string schoolName = "schoolName";
	std::string schoolType = "school";
	std::string address = "China";
public:
	principal* master;
	std::string getSchoolName()
	{
		return schoolName;
	}
	virtual~school()
	{
		cout << schoolName << "�ż���" << endl;
		delete master;
	}

	school(principal* master, std::string schoolName) :school(master, schoolName, "Ĭ������", "Ĭ�ϵ�ַ")
	{
		
	}
	school(principal* master, std::string schoolName,std::string schoolType,std::string address)
	{
		this->master = master;
		this->schoolName = schoolName;
	}
	school(std::string schoolName, std::string schoolType, std::string address) :school(new principal("��ʦ"), schoolName, schoolType, address){
		cout << "��ͨ����" << endl;
	}
	school(const school& p) :school(new principal(*(p.master)),p.schoolName,p.schoolType, p.address){
		cout << this->schoolName << "����������" << endl;
	}
	school(school && other) :school(other.master, other.schoolName, other.schoolType, other.address)
	{
		cout << "�ƶ�����" << endl;
		other.master = NULL;
	}
	virtual void schoolOpens()
	{
		cout << this->schoolName << "��ѧ��" << endl;
	}
};
void printSchool(school * school)
{
	school->schoolOpens();
	delete school;
}
void printSchool(school & school)
{
	school.schoolOpens();
	delete &school;
}
class university :public school
{
public:
	university() :school("����ָ��", "������ѵ", "����")
	{
		cout << "��ѧ����" << endl;
	}
	void schoolOpens()//����
	{
		cout << "��ѧ��ѧ��" << endl;
		//school::schoolOpens();//��ʽ����
	}
	~university()
	{
		cout << "��ѧ����" << endl;
	}
};

class highschool :public school
{
public:
	highschool() :school("��ˮ��ѧ", "����", "��ˮ")
	{
		cout << "���й���" << endl;
	}
};

class vec
{
	std::vector<int>arr;
public:
	vec(initializer_list<int> list) :arr(list)
	{
	}
	int& operator [](int index)
	{
		assert(index>=0&&index<arr.size());
		return arr[index];
	}
};


class tool
{
	int *p;
public:
	tool()
	{
		cout << "tool������" << endl;
	}
	tool(int t)
	{
		cout << "tool������������" << endl;
	}
	tool(const tool&)
	{
		cout << "tool����������" << endl;
	}
	tool(tool&&)
	{
		cout << "tool�ƶ�������" << endl;
	}
	~tool()
	{
		cout << "tool������" << endl;
	}
	tool & operator=(tool&&)
	{
		cout << "tool�ƶ���ֵ��" << endl;
		return *this;
	}
	tool &operator=(const tool&)
	{
		cout << "tool������ֵ��" << endl;
		return *this;
	}
};

class A
{
	tool t = 2;
public:
	A() :t(5)
	{
		
	}
};


int main()
{

	vec v{1,2,3,4,5,6,7};
	
	cout << v[2] << endl;
	
	return 0;
}