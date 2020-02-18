#include"weakptr.h"
#include<iostream>
using namespace std;
class node
{
public:
	lan::L_sharedPtr<node>pre;
	lan::L_sharedPtr<node>next;
	~node()
	{
		cout << "节点已析构" << endl;
	}
};
int main()
{
	lan::L_sharedPtr<node>node1 = {new node};
	lan::L_sharedPtr<node>node2 = { new node };
	cout << node1->next.use_count() << endl;
	node1->next = node2;
	node2->pre = node1;
	cout << node1.use_count() << endl;
}