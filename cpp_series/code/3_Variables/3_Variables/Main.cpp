#include <iostream>

int main()
{
	char a = 5;
	std::cout << sizeof(a) << std::endl;
	short b = 5;
	std::cout << sizeof(b) << std::endl;
	int c = 5;
	std::cout << sizeof(c) << std::endl;
	long d = 5;
	std::cout << sizeof(d) << std::endl;
	float e = 5.5f;
	std::cout << sizeof(e) << std::endl;
	double f = 5.5;
	std::cout << sizeof(f) << std::endl;
	bool g = 5;
	std::cout << sizeof(g) << std::endl;


	/*
	bool variable = 5;
	std::cout << variable << std::endl;
	*/

	/*
	float variable = 5.5f;
	double variable = 5.5;
	std::cout << variable << std::endl;
	*/

	/*
	short a = 'A';
	std::cout << a << std::endl;
	a = 65;
	std::cout << a << std::endl;
	*/

	/*
	char a = 'A';
	std::cout << a << std::endl;
	a = 65;
	std::cout << a << std::endl;
	*/

	/*
	int variable = 8;  //有符号整数 -2.1b ~ 2.1b
	std::cout << variable << std::endl;
	variable = 20;
	std::cout << variable << std::endl;

	unsigned int variable = 8;  //无符号整数 0 ~ 4.2b
	*/

	std::cin.get();
}