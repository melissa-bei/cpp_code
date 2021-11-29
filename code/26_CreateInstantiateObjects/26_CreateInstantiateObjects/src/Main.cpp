#include <iostream>
#include <string>

using String = std::string;  //Ϊʲô��ʹ��using std::�Ժ�ὲ��

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
		Entity entity0;  //ֻҪ�й��캯����һ�оͲ��ᱨ��
		std::cout << entity0.GetName() << std::endl;

		Entity entity1("Melissa");
		e = &entity1;

		Entity entity2 = Entity("Melissa");  //����c++����ɿ�������ʵ������ʽ

		Entity* entity3 = new Entity("Melissa");
		e = entity3;
		std::cout << entity3->GetName() << std::endl;
	}
	std::cin.get();
	delete e;
}