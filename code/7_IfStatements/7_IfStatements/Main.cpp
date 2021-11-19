#include <iostream>
#include "Log.h"


int main()
{
	int x = 6;
	if (x == 5)
		Log("HelloWorld");
	else
		Log("Unequal");

	std::cin.get();
}