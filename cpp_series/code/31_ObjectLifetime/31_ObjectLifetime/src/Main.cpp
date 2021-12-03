#include <iostream>
#include <string>


class Entity
{
public:
	Entity() { std::cout << "Created Entity!" << std::endl; }
	~Entity() { std::cout << "Destroyed Entity!" << std::endl; }
};

int* CreateArray()
{
	int array[50];  //在stack中创建一个array，并返回指向那块stack内存的指针
	array[0] = 1;
	return array;  //尝试去返回指针指向的内存
}  //但是当代码执行到这一行，array所指向的那部分内存因为是属于stack的，所以在这里会被释放，导致实际上返回的是一块未初始化的空间

class ScopedPtr
{
private:
	Entity* m_Ptr;
public:
	ScopedPtr(Entity* ptr)
		:m_Ptr(ptr)
	{
	}

	~ScopedPtr()
	{
		delete m_Ptr;
	}
};

int main()
{
	int* a = CreateArray();

	{
		Entity e;
		Entity* e1 = new Entity();
		ScopedPtr e2 = new Entity();
		ScopedPtr e3(new Entity());
	}

	std::cin.get();

}