#include <iostream>
#include <string>

class Entity
{
private:
	int * m_X,* m_Y, * m_Z;
	mutable int var;
public:
	int* GetX() const
	{ 
		var = 0;
		return m_X;
	}
	int* GetY()
	{
		return m_Y;
	}
	int* GetZ()
	{
		return m_Z;
	}
};

void PrintEntity(const Entity& e)
{
	std::cout << e.GetX() << std::endl;
}

int main()
{
	Entity e;
	PrintEntity(e);

	const int MAX_AGE = 90;  //定义一个常量

	int* a = new int;

	*a = 2;  //修改指针指向的内容
	std::cout << *a << std::endl;
	a = (int*)&MAX_AGE;  //修改指向的地址
	std::cout << *a << std::endl;


	/*
	//////////////////////////////////////////////

	const int* b = new int;
	int const* e = new int;

	*b = 2;  //不能修改指针指向的内容
	std::cout << *b << std::endl;
	b = (int*)&MAX_AGE;  //修改指向的地址
	std::cout << *b << std::endl;
	//////////////////////////////////////////////

	int* const c = new int;

	*c = 2;  //修改指针指向的内容
	std::cout << *c << std::endl;
	c = (int*)&MAX_AGE;  //不能修改指向的地址
	std::cout << *c << std::endl;
	//////////////////////////////////////////////

	const int* const d = new int;

	*d = 2;  //不能修改指针指向的内容
	std::cout << *d << std::endl;
	d = (int*)&MAX_AGE;  //不能修改指向的地址
	std::cout << *d << std::endl;
	*/

	std::cin.get();
}