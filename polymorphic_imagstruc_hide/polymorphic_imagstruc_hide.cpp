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
		cout <<schoolName<< "�ż���" << endl;
		delete master;
	}
	school()
	{
		cout << "Ĭ�Ϲ���" << endl;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "��ͨ����" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("��ʦ");
	}
	school(const school& p) :schoolType(p.schoolType), address(p.address){
		schoolName = p.schoolName;
		cout << this->schoolName << "����������" << endl;
		master = new principal(*(p.master));
	}
	school(school && other) :schoolType(other.schoolType), schoolName(other.schoolName), address(other.address)
	{
		cout << "�ƶ�����" << endl;
		master = other.master;
		other.master = NULL;
	}
	virtual void schoolOpens()
	{
		cout << this->schoolName<<"��ѧ��" << endl;
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
	university() :school("����ָ��","�����ѵ","����")
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