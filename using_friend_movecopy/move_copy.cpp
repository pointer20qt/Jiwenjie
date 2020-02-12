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
		cout << "下班了" << endl;
	}
};

class school{
public:
	std::string schoolName;
	std::string schoolType;
	std::string address;
	principal* master;
	~school()
	{
		cout << "放假了" << endl;
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "构造了" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("老师");
	}
	school(const school& p) :schoolType(p.schoolType), address(p.address){
		schoolName = this->schoolName;
		cout << this->schoolName << "拷贝建立了" << endl;
		master = new principal(*(p.master));
	}
	school(school && other) :schoolType(other.schoolType), schoolName(other.schoolName), address(other.address)
	{
		cout << "移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}

};
school getschool()
{
	school s2("东油","大学","大庆");
	return s2;
}
int main()
{
	school s("东油", "大学", "大庆");
	school s2(std::move(s));
	//school s2(s);
	//school s1(getschool());
	return 0;
}