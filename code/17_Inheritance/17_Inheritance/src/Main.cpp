#include <iostream>

class Entity
{
public:
	float x, y;

	void Move(float xa, float ya)
	{
		x += xa;
		y += ya;
	}
};

class Player : public Entity
{
public:
	const char* Name;

	void PrintName()
	{
		std::cout << Name << std::endl;
	}
};

int main()
{
	std::cin.get();
}