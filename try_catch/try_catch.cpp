#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int>arr{1,2,3,4};
	
	try
	{
		arr.at(5);
	}
	/*catch (...)
	{
		cout << "�����쳣" << endl;
	}*/
	catch (out_of_range& e)
	{
		cout << "����Խ���쳣" << endl;
	}
	return 0;
}