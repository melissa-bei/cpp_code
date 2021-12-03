#include <iostream>


class Entity
{
public:
	static const int exampleSize = 5;
	int example[exampleSize];

	Entity()
	{
		int size = sizeof(example);
		std::cout << size << std::endl;
		int count = sizeof(example) / sizeof(int);
		std::cout << count << std::endl;
		for (int i = 0; i < exampleSize; i++)
		{
			example[i] = 2;
		}
	}
};

class Entity2
{
public:
	int* another = new int[5];

	Entity2()
	{
		int size = sizeof(another);
		std::cout << size << std::endl;
		int count = sizeof(another) / sizeof(int);
		std::cout << count << std::endl;
		for (int i = 0; i < 5; i++)
		{
			another[i] = 2;
		}
	}
};


int main()
{
	Entity e;
	Entity2 e2;

	std::cin.get();
}