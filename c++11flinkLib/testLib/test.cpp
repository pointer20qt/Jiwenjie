#include "test.h"
#include<iostream>

test::test()
{
	std::cout << "������" << std::endl;
}
void test::run(){
	std::cout << __FUNCTION__ << std::endl;
}

test::~test()
{
	std::cout << "������" << std::endl;
}
