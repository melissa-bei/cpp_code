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
	int* ptr = &var;  //��ֵΪ0���Ǳ�ʾ���ָ��ʽ��Ч�ģ�Ҳ����������һ����Ч���ڴ��ַ��
	*ptr = 10;
	LOG(var);
	*/
	std::cin.get();
}