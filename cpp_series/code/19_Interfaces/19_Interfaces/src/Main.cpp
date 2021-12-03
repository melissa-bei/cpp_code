#include <iostream>
#include <string>

class Printable
{
public:
	virtual std::string GetClassName() = 0;  //��GetClassName�������麯��
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
		: m_Name(name) {}  //���ﹹ�캯��ʹ���˶����б��ڹ��������ں�����ִ�У�����name��ֵ��m_Name

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
	Entity* e = new Entity();  //����ʵ��������
	//PrintName(e);
	Print(e);

	Player* p = new Player("Player");
	//PrintName(p);
	Print(p);

	std::cin.get();
}