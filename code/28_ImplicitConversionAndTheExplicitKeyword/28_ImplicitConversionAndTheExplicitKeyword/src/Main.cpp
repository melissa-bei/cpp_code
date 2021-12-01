#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
	int m_Age;
public:
	Entity(const std::string& name)
		:m_Name(name), m_Age(-1) {}
	explicit Entity(int age)
		:m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity& entity)
{
}


int main()
{
	Entity a("Melissa");
	Entity b = std::string("Melissa");
	Entity c(22);
	//Entity d = 22;
	//PrintEntity(22);
	PrintEntity(Entity("Melissa"));
	std::cin.get();
}