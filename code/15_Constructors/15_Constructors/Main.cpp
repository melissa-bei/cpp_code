#include <iostream>

class Entity
{
public:
	float X, Y;

	Entity()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Entity(float x, float y)
	{
		X = x;
		Y = y;
	}

	void Init()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	void Print()
	{
		std::cout << "X=" << X << ",Y=" << Y << std::endl;
	}

	~Entity()
	{

	}
};

class Log
{
private:
	Log() {};  //隐藏构造函数，就不能从外部进行实例化
	//Log() = delete;
public:
	static void Write()
	{

	};
};

int main()
{
	Log::Write();
	Log l;
	Entity e(10.0f, 5.0f);
	e.Print();
	std::cin.get();
}