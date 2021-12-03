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
	int array[50];  //��stack�д���һ��array��������ָ���ǿ�stack�ڴ��ָ��
	array[0] = 1;
	return array;  //����ȥ����ָ��ָ����ڴ�
}  //���ǵ�����ִ�е���һ�У�array��ָ����ǲ����ڴ���Ϊ������stack�ģ�����������ᱻ�ͷţ�����ʵ���Ϸ��ص���һ��δ��ʼ���Ŀռ�

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