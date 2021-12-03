#include <iostream>
#include <string>

class Entity
{
public:
	virtual std::string GetName() { return "Entity"; }
};

class Player : public Entity
{
public:
	std::string m_Name;
public:
	Player(const std::string& name)
		: m_Name(name){}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

	std::string GetName() override { return m_Name; }
};


void PrintName(Entity* entity)
{
	std::cout << entity->GetName() << std::endl;
}


int main()
{
	Entity* e = new Entity();
	PrintName(e);

	Player* p = new Player("Player");
	PrintName(p);


	Entity* entity = p;
	PrintName(entity);

	std::cin.get();
}