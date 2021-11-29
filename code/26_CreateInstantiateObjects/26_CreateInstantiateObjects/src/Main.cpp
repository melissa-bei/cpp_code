#include <iostream>
#include <string>

using String = std::string;  //为什么不使用using std::以后会讲到

class Entity
{
private:
	String m_Name;
public:
	Entity() : m_Name("Unknown") { }
	Entity(const String& name) : m_Name(name) { }

	const String& GetName() { return m_Name; }
};

int main()
{
	Entity* e;
	{
		Entity entity0;  //只要有构造函数这一行就不会报错
		std::cout << entity0.GetName() << std::endl;

		Entity entity1("Melissa");
		e = &entity1;

		Entity entity2 = Entity("Melissa");  //这是c++中最可控且最快的实例化方式

		Entity* entity3 = new Entity("Melissa");
		e = entity3;
		std::cout << entity3->GetName() << std::endl;
	}
	std::cin.get();
	delete e;
}