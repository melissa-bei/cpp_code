#include <iostream>

#define LOG(x) std::cout << x << std::endl;

void Increment(int& value)
{
	value++;
}

int main()
{
	int a = 5;
	Increment(a);
	LOG(a);


	/*
	int a = 5;
	//int* ptr = &a;
	int& ref = a;

	ref = 2;
	LOG(ref);
	*/

	std::cin.get();
}