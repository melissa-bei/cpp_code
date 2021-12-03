#include <iostream>

int Multiply(int a, int b)
{
	return a * b;
}


void MultiplyAndLog(int a, int b)
{
	int result = Multiply(a, b);
	std::cout << result << std::endl;
}


int main()
{
	MultiplyAndLog(3, 2);
	MultiplyAndLog(8, 5);
	MultiplyAndLog(90, 45);

	/*
	int result = Multiply(3, 2);
	std::cout << result << std::endl;
	int result2 = Multiply(8, 5);
	std::cout << result2 << std::endl;
	int result3 = Multiply(90, 45);
	std::cout << result3 << std::endl;
	*/

	std::cout << "HelloWorld" << std::endl;
	std::cin.get();
}