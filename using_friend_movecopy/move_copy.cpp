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
		cout << "�°���" << endl;
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
		cout << "�ż���" << endl;
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "������" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("��ʦ");
	}
	school(const school& p) :schoolType(p.schoolType), address(p.address){
		schoolName = this->schoolName;
		cout << this->schoolName << "����������" << endl;
		master = new principal(*(p.master));
	}
	school(school && other) :schoolType(other.schoolType), schoolName(other.schoolName), address(other.address)
	{
		cout << "�ƶ�����" << endl;
		master = other.master;
		other.master = NULL;
	}

};
school getschool()
{
	school s2("����","��ѧ","����");
	return s2;
}
int main()
{
	school s("����", "��ѧ", "����");
	school s2(std::move(s));
	//school s2(s);
	//school s1(getschool());
	return 0;
}