#include<iostream>
#include<time.h>
#include<math.h>
using namespace std;
//����[0��a)���� rand()%20
//����[a,b)���� rand()%(b-a)+a
//����0~1  double p =((double)rand())/RAND_MAX;
//����a~b���С��  rand()%(b-a)+a
bool probability(double n)
{
	double p =((double)rand())/RAND_MAX;
	if (p<(n))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	srand(time(0));
	int t = 0, f = 0;
	for (int i = 0; i < 100; i++)
	{
	
		if (probability(0.005))
		{
			t++;
			cout << "����" << endl;
		}
		else
		{
			f++;
			cout << "û����" << endl;
		}
	}
	cout << t << "��" << f << endl;
	return 0;
}