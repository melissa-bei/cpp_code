#include <iostream>

extern int s_Variable;

struct Entity
{
	static int x, y;

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

int Entity::x;
int Entity::y;

class Singleton
{
private:
	int x = 0;
public:
	static Singleton& Get()
	{ 
		static Singleton instance;  //��Ϊ�ǵ����࣬����˽��������һ��ָ����ʵ���ָ��
		return instance;
	}  //���ﷵ�ص��ǵ������ʵ��

	void Hello()
	{
		std::cout << x << std::endl;
	}
	void Set(int value)
	{
		x = value;
	}
};

void Function()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

int main()
{
	Singleton s;
	s.Get().Hello();
	s.Get().Set(2);
	Singleton::Get().Hello();
	Singleton::Get().Set(5);
	Singleton::Get().Hello();
	Singleton::Get().Set(10);
	Singleton::Get().Hello();
	s.Get().Hello();

	Function();
	Function();
	Function();

	/*
	Entity e;
	e.x = 2;
	e.y = 3;
	e.Print();
	Entity e1;
	e1.x = 5;
	e1.y = 8;
	e1.Print();
	*/
	std::cin.get();
}