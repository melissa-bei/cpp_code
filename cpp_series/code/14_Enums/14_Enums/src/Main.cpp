#include <iostream>

enum Example : unsigned char
{
	A = 3, B = 2, C = 5
};

int main()
{
	Example value = A;
	std::cin.get();
}