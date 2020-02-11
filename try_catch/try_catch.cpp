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
		cout << "出现异常" << endl;
	}*/
	catch (out_of_range& e)
	{
		cout << "数组越界异常" << endl;
	}
	return 0;
}