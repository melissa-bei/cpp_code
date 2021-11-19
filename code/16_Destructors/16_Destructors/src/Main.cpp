#include <iostream>

class Entity
{
public:
	float X, Y;

	Entity()
	{
		X = 0.0f;
		Y = 0.0f;
		std::cout << "Created Entity!" << std::endl;
	}

	Entity(float x, float y)
	{
		X = x;
		Y = y;
	}

	void Init()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	void Print()
	{
		std::cout << "X=" << X << ",Y=" << Y << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}
};

void Function()
{
	Entity e;
	e.Print();
}



int main()
{
	Function();

	std::cin.get();
}