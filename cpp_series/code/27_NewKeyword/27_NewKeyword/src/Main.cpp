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
	int a = 2;
	int* b = new int;
	int* c = new int[50];
	
	Entity* e = new(c) Entity();

	delete b;
	delete[] c;

	std::cin.get();
}