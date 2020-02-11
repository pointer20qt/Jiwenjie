#include "test.h"
#include<iostream>

test::test()
{
	std::cout << "创建了" << std::endl;
}
void test::run(){
	std::cout << __FUNCTION__ << std::endl;
}

test::~test()
{
	std::cout << "析构了" << std::endl;
}
