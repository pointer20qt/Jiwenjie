#include<iostream>
#include<vector>
#include<string>

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
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
	principal* master;
	std::string getSchoolName()
	{
		return schoolName;
	}
	virtual~school()
	{
		cout <<schoolName<< "放假了" << endl;
		delete master;
	}
	school()
	{
		cout << "默认构造" << endl;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "普通构造" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("老师");
	}
	school(const school& p) :schoolType(p.schoolType), address(p.address){
		schoolName = p.schoolName;
		cout << this->schoolName << "拷贝建立了" << endl;
		master = new principal(*(p.master));
	}
	school(school && other) :schoolType(other.schoolType), schoolName(other.schoolName), address(other.address)
	{
		cout << "移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}
	virtual void schoolOpens()
	{
		cout << this->schoolName<<"开学了" << endl;
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
class university:public school
{
public:
	university() :school("大庆指针","软件培训","大庆")
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

int main()
{
	//university u;
	//school * sp= &u;
	//school & sr = u;
	university *u = new university();
	school* s = new university();
	printSchool(u);
	return 0;
}