#include <iostream>
#include <string>
#include <vector>

struct Vectex
{
	float x, y, z;

	Vectex()
	{}

	Vectex(float x, float y, float z)
		:x(x), y(y), z(z)
	{
	}

	Vectex(const Vectex& vertex)
		:x(vertex.x), y(vertex.y), z(vertex.z)
	{
		std::cout << "Copied!" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& stream, Vectex vectex)
{
	stream << vectex.x << ", " << vectex.y << ", " << vectex.z;
	return stream;
}

int main()
{
	std::vector<Vectex> vertices2;
	vertices2.reserve(3);
	vertices2.emplace_back(1, 2, 3 );
	vertices2.emplace_back(4, 5, 6 );
	vertices2.emplace_back(7, 8, 9 );
	vertices2.push_back({ 10, 11, 12 });

	/*
	Vectex* vertices = new Vectex[5];
	vertices[0] = Vectex({1, 2, 3 });

	std::vector<Vectex> vertices2;
	vertices2.push_back({ 1, 2, 3 });
	vertices2.push_back({ 4, 5, 6 });
	for (int i = 0; i < vertices2.size(); i++)
		std::cout << vertices2[i] << std::endl;

	//vertices2.clear();
	vertices2.erase(vertices2.begin());

	for (Vectex& v : vertices2)
		std::cout << v << std::endl;
	*/
	std::cin.get();
}