#include <iostream>
#include <string>

//void PrintEntity(Entity* e);
void PrintEntity(const Entity& e);


class Entity
{
public:
	int x, y;

	Entity(int x, int y)
	{
		this->x = x;
		this->y = y;

		Entity& ee = *this;
		delete this;
		//PrintEntity(this);
		//PrintEntity(*this);
	}

	int GetX() const
	{
		const Entity& ee = *this;
		return x;
	}

};
/*
void PrintEntity(Entity* e)
{
	std::cout << "Pointer" << std::endl;
}
*/
void PrintEntity(const Entity& e)
{
	std::cout << "Reference" << std::endl;
}


int main()
{
	Entity e = Entity(1, 1);
	std::cin.get();
}