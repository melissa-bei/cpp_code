#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main()
{
	char* buffer = new char[8];
	memset(buffer, 0, 8);

	char** ptr = &buffer;


	delete[] buffer;

	/*
	int var = 8;
	int* ptr = &var;  //赋值为0，是表示这个指针式无效的，也就是它不是一个有效的内存地址。
	*ptr = 10;
	LOG(var);
	*/
	std::cin.get();
}