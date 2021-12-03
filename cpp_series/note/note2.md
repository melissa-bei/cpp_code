C++

## 15. Classes in C++

JAVA、C#本质上也是面向对象的语言，对于这两种语言来说最好不要编写其他风格的程序，总的来说这两种语言只适合面向对象编程。

然而C++不同的地方在于它不仅仅支持面向对象变成，事实上C++支持面向过程、基于对象、面向对象、泛型编程四种。

### 15.1. 类的本质

类本质上是一种将数据和函数组织在一起的方式。

**当创建一个类时，可以指定类中属性的可见性。默认情况下，类中的成员的访问控制都是私有的，意味着只有类内部的函数可以访问这些变量。**

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

class Player  //定义一个玩家类
{
public:  //指定下面变量能够从类外访问
	int x, y;  //包含玩家坐标
	int speed = 2;  //玩家移动速度
};

int main()
{
	Player player;
	player.x = 5;

	std::cin.get();
}
```

添加一个移动玩家位置的方法：

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

class Player
{
public:
	int x, y;
	int speed = 2;

	void Move(int xa, int ya)
	{
		x = xa * speed;
		y = ya * speed;
	}
};

int main()
{
	Player player;
	player.Move(1, -1);

	std::cin.get();
}
```

### 15.2. Classes vs Structs in C++

结构体和类一样都是将数据和函数组织在一起，唯一的区别是**类默认所有内容都是私有的，而结构体默认都是共有的。**

C++中结构体存在的唯一原因是它想要维持与C之间的兼容性，因为C中没有类，但是它含有结构体，如果突然完全删去struct这个关键字，那就会失去所有兼容性。因为C++的编辑器不知道什么是struct，但是我们可以通过`#define`来解决这个问题，`#define struct class`这会将所有的struct替换为class。

那么既然这两个关键字没有本质的区别，那我们在使用中会有区别吗？

结果当然是没有的，但是由多年开发经验总结，struct推荐仅仅用来表示一堆变量，它的意义相当于数学中的向量类，如下从根本上说这个Vec2 struct只是两个浮点数的表现形式，我们只是把他们按字面意义上组合起来为了便于使用。

```c++
struct Vec2
{
    float x, y;
}
```

但是这不意味着我们不打算向里面添加方法，如下面我们只是添加了一个函数来操作这些变量，Add方法将两个Vec2向量加起来，但是最终我们讨论的还是这两个变量。

```c++
struct Vec2
{
    float x, y;
    
    void Add(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }
}
```

另一个要注意的地方是继承，不建议对struct进行继承，如果我们要用一个完整的类层次或某种继承层次建议使用class。因为继承又增加了一层复杂性，而我们想让struct仅仅是数据的结构体。

如果我们由一个类A，一个结构体B它继承自A，一些编译器会发出警告，警告你正在从一个类继承但是你本身只是一个结构体，但这只是警告代码照样可以运行。



## 16. How to write a C++ class

写一个简单的Log Class，以及一个高级一点的改进版本。

日志类是给我们管理log信息的一个方式，换句话说就是我们想要程序打印到控制台的消息或信息，这通常用于调试目的，它可以真正帮助我们在开发中查看具体进度。因为我们应用程序中的控制台十几场就像一个信息转储，我们可以使用它来打印正在发生的事情，控制台基本是内嵌在操作系统中的东西，我们可以保证它一定能正常运作。

作者在这里使用Log类作为示例，是因为Log系统可以根据的需要变得简单或复杂。Log系统不仅可以打印到控制台，还可以打印不同颜色、将log信息输出到一个文件或者网络……。

我们这里要写的是一个包含log等级的简单Log类，等级分为error、warning、message or trace。

如下：

```c++
#include <iostream>

class Log
{
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level)
	{
		m_LogLevel = level;
	}

	void Error(const char* massage)
	{
		if (m_LogLevel >= LogLevelError)
			std::cout << "[ERROR]: " << massage << std::endl;
	}

	void Warn(const char* massage)
	{
		if (m_LogLevel >= LogLevelWarning)
			std::cout << "[WARNING]: " << massage << std::endl;
	}

	void Info(const char* massage)
	{
		if (m_LogLevel >= LogLevelInfo)
			std::cout << "[INFO]: " << massage << std::endl;
	}
};

int main()
{
	Log log;
	log.SetLevel(log.LogLevelError);
	log.Error("Hello");
	log.Warn("Hello");
	log.Info("Hello");
	std::cin.get();
}
```

上面代码中第10行，这里m_是约定好的，它表示这是一个私有的类成员变量，这样在函数内部写代码时就能够区分那些类作用于的一部分、哪些是成员变量、哪些是局部变量。

上述的代码只是一个最简单的Log类，但他并不是一个比较好的代码，只是比较简单易于理解。但是这提供了我们优化这个类的理由，后续会对上面代码进行优化，给出改进写法并说明为什么这么改。



## 17. Static in C++

C++中static实际上有两个含义取决于使用关键字时的上下文，其中一种是在一个类或者一个结构体之外使用，另一种是在类或结构体内部使用。基本上，类外部的static修饰意味着你的声明在link阶段是局部的，也就是它只对定义它的translation unity（.obj）是可见的。而类或结构体中的静态变量，意味着这部分内存实际上是这个类的所有实例共享的，也就是说，即使实例化了很多次这个类或结构体，那个静态变量也只有一个实例。类里面的静态方法也一样，静态方法里没有该实例的指针（this）。

### 17.1. 类或结构体外的static

这节讨论类或结构体外的static。下面的static关键字表示这个变量在link的时候只对这个编译单元（.obj）里的东西可见。

Stasic.cpp

```c++
static int s_Variable = 5;
```

Main.cpp

```c++
#include <iostream>

int s_Variable = 10;

int main()
{
	std::cout << s_Variable << std::endl;
	std::cin.get();
}
```

直接编译执行项目，发现不报错并打印出10。但如果去掉Static.cpp中的static关键字，就会报出link error。也就是说我们不能有两个一样名字一样的全局变量。![image-20211109105639433](E:\newbie\cpp_code\images\image-20211109105639433.png)

一种解决方法是去掉Main.cpp中的赋值，并加上extern关键字，他就会在另外的编译单元中找定义。这特叫做外部链接。如下会打印出5。

Main.cpp

```c++
#include <iostream>

extern int s_Variable;

int main()
{
	std::cout << s_Variable << std::endl;
	std::cin.get();
}
```

但是如果这时我们给Stasic.cpp里的s_Variable加上static关键字，也就意味着我们定义了一个当前文件中的私有变量，其他的编译单元不能访问s_Variable，linker在全局作用域下找不到它，就会报出未知外部符号的link error。

![image-20211109110427391](E:\newbie\cpp_code\images\image-20211109110427391.png)

对于函数是同样的。

我们使用static的时机与class的成员用private类似，基本上只要我们不想让变量时全局可见的，static想用多少就用多少，因为如果不带static关键字定义全局变量的话，就会发现linker在所有的二编译单元中都能检测到它，它是绝对全局的，也就可能导致奇奇怪怪的bug。

总而言之，尽可能让全局函数和变量变成静态的，除非我们必须要将他们用在其他的编译单元里。

### 17.2. 类或结构体内的static

通常面向对象的编程中，类或结构体内部的static，如果用在变量上意味着在所有的类的实例中只会有一个那个变量的实例。用这个类实例化的对象共享这一个static变量，也就是说如果我们在一个类实例中改变静态变量的值，那么就会改变所有类实例中的值，它就相当于这个类中的全局变量。

如果用在方法上也是类似的，类中静态方法没有访问实例的权限，静态方法可以在没有实例化的情况下调用，在静态方法之中也不能写代码去引用类实例，因为我们没有类实例来引用。

如下，正常打印出2, 3和5, 8

Main.cpp

```c++
#include <iostream>

struct Entity
{
	int x, y;

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

int main()

{
	Entity e;
	e.x = 2;
	e.y = 3;
	e.Print();
	Entity e1 = { 5, 8 };
	e1.Print();
	std::cin.get();
}
```

但是如果我们把第五行x和y替换成静态变量，则20行的实例化定义就会报错，是因为这是x和y就不再是class成员了。抛弃这一点和上面e同样的定义方法，

```c++
	static int x, y;
```

```c++
	Entity e1;
	e1.x = 5;  //这里赋值显然和e指向的是两个不同的实例
	e1.y = 8;
```

运行代码，就会报出如下错误，这是因为我们需要在其他地方定义这两个静态变量。

![image-20211109113438066](E:\newbie\cpp_code\images\image-20211109113438066.png)

```c++
#include <iostream>


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

int main()

{
	Entity e;
	e.x = 2;
	e.y = 3;
	e.Print();
	Entity e1;
	e1.x = 5;  //这里赋值显然指向的是两个不同的实例
	e1.y = 8;
	e1.Print();
	std::cin.get();
}
```

再次运行代码后发现，两次都打印出了5, 8。实际上当我们在类型中定义静态变量时，实际上不同实例中的相同变量这实际上指向的是同一块内存，因此子啊任何实例中修改这个静态变量都会直接修改同一块内存的内容，因此，对于静态变量可以通过类名.变量名的方式进行访问，并非一定要进行实例化。

```c++
	Entity::x = 5;  //这里赋值显然指向的是两个不同的实例
	Entity::y = 8;
```

其实相当于我们在Entity的命名空间下定义了两个变量x和y，它实际上不属于class，我们在实例化进行资源时与它并无关系。同意写法后就发现我们实际上修改的是同一个变量。

```c++
#include <iostream>


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

int main()

{
	Entity e;
	Entity::x = 2;
	Entity::y = 3;
	e.Print();
	Entity e1;
	Entity::x = 5;  //这里赋值显然指向的是两个不同的实例
	Entity::y = 8;
	e1.Print();
	std::cin.get();
}
```

同样的我们也可以定义一个全局变量，或者静态全局变量，它依旧会进行link只是不会在出现在整个项目中。上述处理与类中定义静态变量是一样的效果，那么把这些静态变量放入Entity是因为这么处理比较合理，如果我们有一块内存数据想要在所有实例中都共享，把它放在Entity类中就是比较合理的了，就是做局部通用的而变量而不是全局的静态变量。

对于静态方法一样的处理

```c++
#include <iostream>

struct Entity
{
	static int x, y;

	static void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

int Entity::x;
int Entity::y;

int main()

{
	Entity e;
	Entity::x = 2;
	Entity::y = 3;
	Entity::Print();
	Entity e1;
	Entity::x = 5;
	Entity::y = 8;
	Entity::Print();
	std::cin.get();
}
```

要注意的是静态方法不能直接访问非静态变量，除非通过实例。是因为静态方法本身不包含实例，这就涉及到类的工作原理，往深细究，根本没有class这么个东西，只是一个类中非静态的变量或方法都包含一个指向当前类的隐藏变量，而静态方法不能获取那个隐藏变量，它就相当于在类外定义一个相同的方法。也就是在调用Print方法是他不知道你所引用的Entity具体是哪个，也就会报错了。

### 17.3. Local static in C++

本地作用域中用static来声明变量，和前面两种用法有些不同，只要我们从声明变量时要考虑的两个点就能理解他们的区别了，这两点就是生命周期（life time）和作用域（scope）。

生命周期是指变量在被删除之前在内存中停留了多久；作用于就是我们能在哪里访问这个变量。

所以静态局部变量允许我们定义一个变量，它的**生命周期时整个程序周期**，但是**作用域被限制在这个函数（命名空间，也可以是if语句或者别的有作用域的地方）里**。静态函数一直放在使用的存储区，直到退出程序。

本地静态变量和类静态变量没有很大差别因为他们的生命周期是一样的，唯一的区别是类作用语中的静态变量可以被类作用域中的任何变量访问，当然我们在函数中声明的静态变量是对函数本地的。

```c++
void Function()
{
	static int i = 0;
}
```

上面的函数，我们第一次调用它时，静态变量的值被初始化为0，后续调用不会再创建一个新的变量。

通过如下方式进行验证，执行下面代码会打印出1 2 3。

```c++
#include <iostream>

void Function()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

int main()
{
	Function();
	Function();
	Function();
	std::cin.get();
}
```

但如果我们去掉static，i每次都会被重新赋值0，因此就会打印出1 1 1。

```c++
#include <iostream>

void Function()
{
	int i = 0;
	i++;
	std::cout << i << std::endl;
}

int main()
{
	Function();
	Function();
	Function();
	std::cin.get();
}
```

Function内部的静态变量等价于把static int i = 0；的声明定义放在函数外

```c++
#include <iostream>

static int i = 0;

void Function()
{
	i++;
	std::cout << i << std::endl;
}

int main()
{
	Function();
	Function();
	Function();
	std::cin.get();
}
```

但是这种两种写法不一样的地方在于，后者可以在函数外其他地方也能访问到这个变量，如果不小心修改了静态变量的值就会出问题，如下代码会打印出1 11 12

```c++
#include <iostream>

static int i = 0;

void Function()
{
	i++;
	std::cout << i << std::endl;
}

int main()
{
	Function();
    i = 10;
	Function();
	Function();
	std::cin.get();
}
```

总的来说如果我们想要共享内存但是又不想要任何地方都能访问到这个变量时就可以定义为本地变量。

还有一种情况是如果我们有一个singleton类，即类只有一个实例，如果我想创建一个单体类而不创建局部静态变量，就是如下的做法，比较复杂。

```c++
#include <iostream>

class Singleton
{
private:
	static Singleton* s_Instance;  //因为是单体类，所以私有属性是一个指向类实体的指针

public:
	static Singleton& Get() { return *s_Instance; }  //这里返回的是单体类的实例

	void Hello() {}
};

Singleton* Singleton::s_Instance = nullptr;

int main()
{
	Singleton::Get().Hello();
	std::cin.get();
}
```

或者可以直接通过局部静态变量来简化单体类

```c++
#include <iostream>

class Singleton
{
public:
	static Singleton& Get()
	{ 
		static Singleton instance;
		return instance;
	}

	void Hello() {}
};

void Function()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

int main()
{
	Singleton::Get().Hello();
	std::cin.get();
}
```

如下，如果我们没有把单体类的实例定义为静态变量，它会在遇到return之后的花括号的时候被销毁，然后函数结束。如果get方法的是结果的复制那没问题，它会将instance复制一份return回去。但如果像上面第六行中返回一个引用就会出现的问题是instance占用的内存已经被销毁了也就无法在使用了。也就是说static大大延长了实例的生命周期

```c++
class Singleton
{
public:
	Singleton& Get()
	{ 
		static Singleton instance;
		return instance;
	}

	void Hello() {}
};
```

## 18. Enums in C++

有事我们可能想使用一些变量为某个值的时候做相应的处理。如果我们直接简单定义整型变量A、B、C时他可能在全局中都是可访问的，如果一不小心修改了其中的值就有可能使某部分代码完全失去作用。因此，推荐使用enum类型，如下定义了一个枚举类型Example，需要分别定义枚举可取内容如A、B、C，在后续实例化并赋值的时候就只能设置为枚举数中的任意一个，而不能设置为集合外的其他值。

```c++
#include <iostream>

enum Example
{
	A, B, C
};

int main()
{
	Example value = A;
	Example value = 5;  //这里就会报错
	std::cin.get();
}
```

但是本质上来说，枚举数也是整形的集合，如果未做特殊设置，它里面元素的值会按照从前到后从0开始的编号，即上面第五行就意味着A=0、B=1、C=2。但是我们也可以给各个符号赋值的，如下，其实这里的A、B、C也只是一个表示的符号而已，具体值取决于我们付给它本身的值。

```c++
enum Example
{
	A = 3, B = 2, C = 5
};
```

还有一个要注意的地方是，我们不需要同时给所有符号赋值，比如下面我们只给A赋值为5，后面的B、C则会自动增加分别为6和7。

```c++
enum Example
{
	A = 5, B, C
};
```

除此之外我们还可以指定枚举的数据类型，设置为什么类型枚举数就占几个字节，当然如果枚举数比较少的话，也可以直接设为char只占用一个字节节省内存

```c++
enum Example : char
{
	A = 5, B, C
};
```

**注意：枚举的必须是整型，也就是不能设置为float等，因为它不是整型。**

回过头看16.里面我们写过的Log类中就是使用简单的罗列定义了三个log的等级，他们本质上就是整数，而且希望LogLevel只能被设置为这几个数，因此可以通过enum类型来进行优化。

![image-20211110165431461](E:\newbie\cpp_code\images\image-20211110165431461.png)

优化后如下：

```c++
#include <iostream>

class Log
{
public:
	enum Level
	{
		LevelError = 0, LevelWarning, LevelInfo  //希望从0开始递增
	};
private:
	Level m_LogLevel = LevelInfo;
public:
	void SetLevel(Level level)  //
	{
		m_LogLevel = level;
	}

	void Error(const char* massage)
	{
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]: " << massage << std::endl;
	}

	void Warn(const char* massage)
	{
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]: " << massage << std::endl;
	}

	void Info(const char* massage)
	{
		if (m_LogLevel >= LevelInfo)
			std::cout << "[INFO]: " << massage << std::endl;
	}
};

int main()
{
	Log log;
	log.SetLevel(Log::LevelError);  //虽然使用enum加了一层花括号，但是它并不是命名空间，变量本质上还是在Log命名空间中的
	log.Error("Hello");
	log.Warn("Hello");
	log.Info("Hello");
	std::cin.get();
}
```



## 19. Constructors in C++

构造函数是一个特殊类型的方法，在我们每次实例化一个类对象时都会被调用。

如下给出一个在创建类时没有使用构造函数的示例：

```c++
#include <iostream>

class Entity
{
public:
	float X, Y;

	void Print()
	{
		std::cout << "X=" << X << ",Y=" << Y << std::endl;
	}
};

int main()
{
	Entity e;
	e.Print();
	std::cin.get();
}
```

如果我们只进行实例化就直接调用Print方法，会得到如下结果，可以看到两个变量都有一个奇怪的值，这个结果是因为我我们在实例化的时候并没有初始化它指向的内存，因此我们会得到那个内存中本身剩下的值。但我们实际想做的事是将这两个变量初始化为某个特定的值，即默认为某个数，当我们没有指定或者赋值为某个值时它的值就是这个默认的数。

![image-20211112013757714](E:\newbie\cpp_code\images\image-20211112013757714.png)

有一个手动处理的方法：在调用Print方法之前先进行检查，因为当我们直接调用e时就会报出e未初始化的错误了。

```c++
int main()
{
	Entity e;
	std::cout << "X=" << e.X << ",Y=" << e.Y << std::endl;  ////////
	e.Print();
	std::cin.get();
}
```

![image-20211112014915962](E:\newbie\cpp_code\images\image-20211112014915962.png)

我们发现Print方法本身并不像我们想像的那样，它能够编译并不报错，是因为它直接打印的时X和Y，而他们俩被初始化为任意的浮点数，因此能够正常执行。

因此，一定程度上我们需要一个初始化部分，在我们每次实例化一个Entity时，如果我们设置了X和Y则给他们赋值，否则把它们设为一个默认值。比如添加一个Init方法，在实例化之后调用就可以解决初始化问题。

```c++
#include <iostream>

class Entity
{
public:
	float X, Y;

	void Init()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	void Print()
	{
		std::cout << "X=" << X << ",Y=" << Y << std::endl;
	}
};

int main()
{
	Entity e;
	e.Init();
	std::cout << "X=" << e.X << ",Y=" << e.Y << std::endl;
	e.Print();
	std::cin.get();
}
```

但是可以看到我们还是需要多花一行去调用这个初始化函数，显得有点多余，代码就不够简洁。由此引出了我们的“构造函数”。

“构造函数”就是当我们实例化一个类对象时首先被调用，它的定义和其他函数一样，只是没有返回值，而且它的名字必须和class的名字相同，定义了一个构造函数之后就不需要Init方法了，下面和上面代码会得到同样的结果。

```c++
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

	void Init()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	void Print()
	{
		std::cout << "X=" << X << ",Y=" << Y << std::endl;
	}
};

int main()
{
	Entity e;
	e.Print();
	std::cin.get();
}
```

实际上当我们没有显式定义构造函数的时候，会调用一个默认的构造函数，它也被设置为默认值，但是它本身是没有做任何事的，基本上等价于

```c++
Entity()
{
}
```

在一些其它语言如Java中，像int、float这种基本类型它自动被初始化为0，但是在c++中并没有这种设定，我们需要手动给这些基本类型赋值，否则他们就被初始化为内存剩下的值了。

**注意：**

- 我们可以用任意多个构造函数，只要他们的参数是不同就行。这一原则与我们写其他同名方法是一样的，即同一方法的重载。

```c++
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

	Entity(float x, float y)  //////////
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
};

int main()
{
	Entity e(10.0f, 5.0f);
	e.Print();
	std::cin.get();
}
```

___

额外的：

如果某个类中只包含一些静态方法时，我们只想让用户通过命名空间直接调用该类中的方法而不对类进行初始化，即该类只是方法的集合，依旧是分开来使用的，而不是有机的组合起来构成一个对象，这是两种不同的策略，后者也就是我们常说的面向对象编程。

为了完成方法的集合----不调用构造函数，

1. 我们可以把构造函数藏起来，即设置为私有的。

```c++
class Log
{
private:
	Log() {};  //隐藏构造函数，就不能从外部进行实例化
public:
	static void Write()
	{

	};
};

int main()
{
    Log::Write();  //支持通过命名空间直接调用方法
    //Log l;  //当隐藏了构造函数后，该行就会报错，达到了不支持实例化效果
}
```

![image-20211112024453863](E:\newbie\cpp_code\images\image-20211112024453863.png)

2. 也可以告诉类我们不需要构造函数。

```c++
class Log
{
private:
	Log() = delete;
public:
	static void Write()
	{

	};
};

int main()
{
    Log::Write();  //支持通过命名空间直接调用方法
    //Log l;  //删除了构造函数后，该行就会报错
}
```

![image-20211112024403061](E:\newbie\cpp_code\images\image-20211112024403061.png)

___

还有一些特殊类型的构造函数，比如Copy Constructor和Move Constructor……



## 20. Destructors in C++

析构函数与构造函数类似，他是当我们要销毁一个对象时，就会调用析构函数。

构造函数通常用来设置变量默认值或者做一些其他的初始化操作的；相应的析构函数就是去初始化所有内容，并清理使用过的内存的方法。

析构函数在栈和堆对象中都适用，即我们通过new创建的（堆）对象，当我们调用delete删除它时就会调用析构函数，如果只是简单的栈对象，当命名空间或者对象要被删除时，就会调用析构函数。

```c++
~Entity()
{

}
```

```c++
#include <iostream>

class Entity
{
public:
	float X, Y;

	Entity()
	{
		X = 0.0f;
		Y = 0.0f;
		std::cout << "Created Entity!" << std::endl;
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
		std::cout << "Destroyed Entity!" << std::endl;
	}
};

void Function()
{
	Entity e;  //运行完打印第一行
	e.Print();  //运行我打印第二行
}  //运行完打印第三行


int main()
{
	Function();

	std::cin.get();
}
```

![image-20211112030501310](E:\newbie\cpp_code\images\image-20211112030501310.png)

通常，如果我们在构造函数中执行了某些初始化代码，相应的我们也会需要在析构函数中逆初始化或者删除所有的内容，如果我们不这么处理就有可能导致内存泄露。

用堆式对象来举例，如果我们手动在对上分配了一些内存，那么就必须手动去清理掉。如果狮子啊Entity的构造函数里分配了堆内存，就必须在析构函数中去清理掉，否则离开Entity之后，他的对象就被清理掉了。



## 21. Inheritance in C++

面向对象编程中最重要且最基础的特性之一就是继承，也是我们在开发过程中可使用的最强大的功能之一。

继承允许我们有一系列以层次接关系关联的类，我们可以创建一个基类只包含基本的功能，然后了可以从该基类继承去派生出不同的子类来实现其他的功能。我们再开发中使用继承的初衷就是为了避免代码重复。

如下是一个示例，Player继承自Entity，它包含了Entity类中的所有成员，Player既是Player类又是Entity类，也就是说我们可以在任何能使用Entity类的地方直接使用Player类，这就是面向对象编程的另一个基本特性**”多态性“**。而且我们只看代码中Player是无法直观知道该类中的所有成员，需要结合他的父类一起看。

简单来说，**多态性就是指一个类包含多种类型。**Player本身包含Entity中的所有对象，甚至会有一些额外成员（也可以没有），也就是说它永远是Entity的一个超子集，那么在任何使用Entity的地方直接使用Player都是可以的，因为它包含了Entity的所有属性。

> 基类中的公有成员在子类中能直接访问。
>
> 那么基类中的私有成员子类中都包含吗？？？？

```c++
#include <iostream>

class Entity  //baseclass
{
public:
	float x, y;

	void Move(float xa, float ya)
	{
		x += xa;
		y += ya;
	}
};

class Player : public Entity  //Player继承自Entity
{
public:
	const char* Name;  //额外添加的成员变量

	void PrintName()  //额外添加的成员方法
	{
		std::cout << Name << std::endl;
	}
};

int main()
{
	Player player;
	player.Move(5, 5);
	player.x = 2;  //像使用Entity一样直接使用player，直接访问他的x
	std::cin.get();
}
```



## 22. Virtual Function in C++

虚函数允许我们在子类中重写父类的方法。

假设我们有两个类A、B，B继承自A，如果我们在A类中创建一个方法并将其指定为virtual，我们就可以选择在B中覆盖该方法来实现.其他的功能

```c++
#include <iostream>
#include <string>

class Entity
{
public:
	std::string GetName() { return "Entity"; }
};

class Player : public Entity
{
public:
	std::string m_Name;
public:
	Player(const std::string& name)
		: m_Name(name){}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

	std::string GetName() { return m_Name; }
};


int main()
{
	Entity* e = new Entity();
	std::cout << e->GetName() << std::endl;

	Player* p = new Player("Player");
	std::cout << p->GetName() << std::endl;

	Entity* entity = p;
	std::cout << entity->GetName() << std::endl;

	std::cin.get();
}
```

当我们想要使用一个Entity类型的指针去指向一个Player对象时，输出的结果是`Entity`的名字。到那时本身是想让它输出`Player`的，虽然使用的是Entity父类本身，但是p自身却实实在在是一个player。

![image-20211124144036362](E:\newbie\cpp_code\images\image-20211124144036362.png)

把打印名字的代码整合成方法，

```c++
#include <iostream>
#include <string>

class Entity
{
public:
	std::string GetName() { return "Entity"; }
};

class Player : public Entity
{
public:
	std::string m_Name;
public:
	Player(const std::string& name)
		: m_Name(name){}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

	std::string GetName() { return m_Name; }
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
```

发现结果输出了三次`Entity`，这并不是我们想要的。我们想要的是实际传入的是什么类型，就去调用相应类型的方法。在PrintName方法中我们可以把Player实例当作Entity实例来使用，但是他识别的是Entity的类型并直接调用该类中第7行的GetName方法，而不是我们设想的去调用Player中第18行的GetName方法。

这一诉求就移除了我们的虚函数，虚函数引入了一种叫做动态分配的东西，通常使用VTable（虚函数表）来实现此编译。虚函数表就是一个包含基类中所有虚函数的的映射，一边在运行时能够映射到正确的重写函数上。

总的来说，如果要覆盖基类中的函数，就需要在基类中将基函数标记为虚函数，仅仅只需要做一行修改，将上面第7 行代码替换为下面的，输出的结果就是我们想要的。

```c++
	virtual std::string GetName() { return "Entity"; }
```

![image-20211124145806083](E:\newbie\cpp_code\images\image-20211124145806083.png)

在c++11中引入的，子类中重写的函数可以加上`override`进行标记，它不是必要的，但是可以提高代码的可读性，而且它可以帮助我们避免一些错误，比如书写错误，即不能重写基类中没有的函数，也不能重写未标记为虚函数的函数。

---

使用虚函数不是毫无代价的，有两个运行时间损耗和虚函数有关：

1. 首先，需要额外的内存中才能将信息存储在虚函数表中，以便我们可以分派到正确的函数，该函数包含实际基类中指向虚函数表的成员指针。
2. 其次，每次调用虚函数的时候需要去遍历虚函数表一查看该映射哪个函数，这是额外的消耗；【一般不会因为性能问题而不去使用虚函数，除非是在性能特别差的嵌入式芯片上等】

```c++
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
		: m_Name(name){}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

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
```

### 22.1 Interfaces in C++（Pure Virtual Functions）

一种特殊的虚函数----纯虚函数，本质上就是其它语言中的抽象方法和接口，如（java和c#），它允许我们定义一个在基类中没有实现的函数，然后迫使在子类中实际实现。

在上一节的实例中，我们可以看到在Entity中有一个GetName函数，然后在Player中重写那个函数，如果在基类中的虚函数带有实际函数体，它意味着我们在子类中可以重写也可以不重写该函数，如果我们没有重写该方法，我们也可以调用player中的GetName方法，但是他是直接调用Entity中的该方法，并返回`Entity`。

然而在某些情况下提供默认实现多我们来说毫无意义，实际上我们可能想要求子类提供自己特定的函数定义。在面向对象编程中，创建一个只包含为实现方法并且交由子类去实现功能的类是非常普遍的，这通常被称为**接口**。

在接口中，类仅仅包含为实现的方法并充当一种勉强的模板，并且由于它不包含实现方法，我们是无法实例化该类。只有当我们同通过继承实现了所有的纯虚函数之后才能进行实例化。

```c++
#include <iostream>
#include <string>

class Printable
{
public:
	virtual std::string GetClassName() = 0;  //将GetClassName方法纯虚函数
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
		: m_Name(name) {}  //这里构造函数使用了定义列表，在构造是先于函数体执行，代表将name赋值给m_Name

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
	Entity* e = new Entity();  //不能实例化该类
	//PrintName(e);
	Print(e);

	Player* p = new Player("Player");
	//PrintName(p);
	Print(p);

	std::cin.get();
}
```



## 23. Visibility in C++

访问控制，实际上是属于面向对象编程的概念，它是说类中成员数据及成员函数的可访问性，可见性指的是谁能访问、谁能调用、谁能使用它们等等。

访问控制对于程序实际运行方式，对程序性能或者类似的性能绝对没有影响，他只是纯粹语言中存在的东西，是我们能更好地编写、组织代码，仅此而已。

### 23.1 C++中有三个基本的访问控制修饰符：

- `public`：公有，任何函数都可以访问。
- `protect`：保护，比私有好一点但是比公有弱，在该类内及所有派生类中都可以访问这些属性。
- `private`：私有，只有该类内才能访问这些变量。

> 这里还有一个`友元` `friend`标识符比较特殊，如果把一个类或者函数标记为Entity类的友元，友元是可以访问类中的私有成员的，后面会涉及到。

### 23.3 应用场景

在实际开发中将所有成员设为公有是不科学的，重要的是要考虑到书写风格、以及针对可能会阅读此代码并可能扩展的人来说如何编写易于维护易于理解的代码，它不会影响性能，也不会产生无关的代码，计算机并不理解这些，这只是人们发明出来帮助他人以及自己的理解罢了。通过指定可见性，我们可以确保别人不要调用其他不该调用的代码，进而导致一些错误。
