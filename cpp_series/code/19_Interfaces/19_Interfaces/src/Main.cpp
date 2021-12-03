#include <iostream>
#include <string>

class Printable
{
public:
	virtual std::string GetClassName() = 0;  //将GetClassName方法纯虚函数
};

class Entity : public Printable
{
public:
	virtual std::string GetName() { return "Entity"; }
	std::string GetClassName() override { return "Entity"; }
};

class Player : public Entity
{
public:
	std::string m_Name;
public:
	Player(const std::string& name)
		: m_Name(name) {}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

	std::string GetName() override { return m_Name; }
	std::string GetClassName() override { return "Player"; }
};


void PrintName(Entity* entity)
{
	std::cout << entity->GetName() << std::endl;
}


void Print(Printable* obj)
{
	std::cout << obj->GetClassName() << std::endl;
}


int main()
{
	Entity* e = new Entity();  //不能实例化该类
	//PrintName(e);
	Print(e);

	Player* p = new Player("Player");
	//PrintName(p);
	Print(p);

	std::cin.get();
}