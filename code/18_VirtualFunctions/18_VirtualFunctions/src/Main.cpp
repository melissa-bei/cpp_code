#include <iostream>
#include <string>

class Entity
{
public:
	std::string GetName() { return "Entity"; }
};

class Player : public Entity
{
private:
	std::string m_Name;
public:
	Player(const std::string& name)
		: m_Name(name){}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

	std::string GetName() { return m_Name; }
};


int main()
{
	Entity* e = new Entity();
	std::cout << e->GetName() << std::endl;

	Player* p = new Player("Player");
	std::cout << p->GetName() << std::endl;

	std::cin.get();
}