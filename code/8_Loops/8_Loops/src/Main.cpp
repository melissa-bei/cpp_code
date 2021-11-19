#include <iostream>
#include "Log.h"

int main()
{
	for (int i = 0; i < 5; i++)
	{
		if (i > 2)
		{
			//continue;
			//break;
			return 0;
		}
		Log("HelloWorld");
		std::cout << i << std::endl;
	}
	std::cin.get();

	/*
	bool condition = false;
	do
	{
		Log("HelloWorld");
	} while (condition);
	Log("====================================");

	int i = 0;
	while (i < 5)
	{
		Log("HelloWorld");
		std::cout << i << std::endl;
		i++;
	}

	Log("====================================");

	i = 0;
	condition = true;
	for ( ; condition; )
	{
		Log("HelloWorld");
		std::cout << i << std::endl;
		i++;
		if (!(i < 5))
			condition = false;
	}
	
	Log("====================================");

	for (int i = 0; i < 5; i++)
	{
		Log("HelloWorld");
		std::cout << i << std::endl;
	}
	std::cin.get();
	*/
}