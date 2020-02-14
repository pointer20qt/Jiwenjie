#include<iostream>
#include<vector>
#include<string>
#include<Initializer_List>
using namespace std;

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
		cout << schoolName << "放假了" << endl;
		delete master;
	}

	school(principal* master, std::string schoolName) :school(master, schoolName, "默认类型", "默认地址")
	{
		
	}
	school(principal* master, std::string schoolName,std::string schoolType,std::string address)
	{
		this->master = master;
		this->schoolName = schoolName;
	}
	school(std::string schoolName, std::string schoolType, std::string address) :school(new principal("老师"), schoolName, schoolType, address){
		cout << "普通构造" << endl;
	}
	school(const school& p) :school(new principal(*(p.master)),p.schoolName,p.schoolType, p.address){
		cout << this->schoolName << "拷贝建立了" << endl;
	}
	school(school && other) :school(other.master, other.schoolName, other.schoolType, other.address)
	{
		cout << "移动构造" << endl;
		other.master = NULL;
	}
	virtual void schoolOpens()
	{
		cout << this->schoolName << "开学了" << endl;
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
	university() :school("大庆指针", "软件培训", "大庆")
	{
		cout << "大学构造" << endl;
	}
	void schoolOpens()//隐藏
	{
		cout << "大学开学了" << endl;
		//school::schoolOpens();//显式调用
	}
	~university()
	{
		cout << "大学析构" << endl;
	}
};

class highschool :public school
{
public:
	highschool() :school("衡水中学", "高中", "衡水")
	{
		cout << "高中构造" << endl;
	}
};

class vec
{
	int * obj;
public:
	vec(std::initializer_list<int>arr)
	{
		obj = new int[arr.size()];
		for (int i = 0; i < arr.size(); i++)
		{
			 obj[i]=*(arr.begin() + i);
		}
		for (auto i = arr.begin(); i != arr.end(); i++)
		{	
			cout << *i << endl;
		}
	}
	int& operator [](unsigned int index)
	{
		return obj[index];
	}
};


class tool
{
	int *p;
public:
	tool()
	{
		cout << "tool构造了" << endl;
	}
	tool(int t)
	{
		cout << "tool单参数构造了" << endl;
	}
	tool(const tool&)
	{
		cout << "tool拷贝构造了" << endl;
	}
	tool(tool&&)
	{
		cout << "tool移动构造了" << endl;
	}
	~tool()
	{
		cout << "tool析构了" << endl;
	}
	tool & operator=(tool&&)
	{
		cout << "tool移动赋值了" << endl;
		return *this;
	}
	tool &operator=(const tool&)
	{
		cout << "tool拷贝赋值了" << endl;
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
	int arr[] = {1,2,3,4,5,6,7};
	vec v({1,2,3,4,5,6,7});
	//vec v = {1,2,3,4,5,6,7};

	cout << v[2] << endl;
	
	A a;
	return 0;
}