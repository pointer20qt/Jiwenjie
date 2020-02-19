#include<iostream>
#include<time.h>
#include<math.h>
using namespace std;
//生成[0，a)的数 rand()%20
//生成[a,b)的数 rand()%(b-a)+a
//生成0~1  double p =((double)rand())/RAND_MAX;
//生成a~b随机小数  rand()%(b-a)+a
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
			cout << "暴击" << endl;
		}
		else
		{
			f++;
			cout << "没暴击" << endl;
		}
	}
	cout << t << "和" << f << endl;
	return 0;
}