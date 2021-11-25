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
		: m_Name(name){}  //���ﹹ�캯��ʹ���˶����б��ڹ��������ں�����ִ�У�����name��ֵ��m_Name

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