## 34. The this keyword in C++

`this`只能在成员函数中使用，成员函数就是一个属于类的函数，在这种函数中我们可以引用this，this就是一个指向当前实例化对象的指针。

在C++类中我们可以定义非静态函数，为了去调用这个函数，我们必须现实例化一个对象，然后再调用函数，也就是说成员函数必须被有效的实例化对象调用，其中的`this`就是指向这个对象的一个指针。

举例：定义一个类Entity，构造一个接受两个int参数的构造函数，如果我们想把接收到的数字分别赋值给类的成员属性，根据之前讲解的内容使用成员初始化列表来实现，如下：

```c++
class Entity
{
public:
	int x, y;

	Entity(int x, int y)
		:x(x), y(y) {}
};
```

但是在学习成员函数列表之前，我们都是在函数体中进行赋值的，如果在上面的代码中我们非要这么做，把复制写在结构体中，就会发现接受的变量名和类的成员属性重名了，这在结构体中实际上是`接受的参数x = 接受的参数x;`，实际接受的值并不会赋给类成员属性，导致两个成员属性经过实例化操作后还是未初始化的状态，如下图：

![image-20211130151533476](E:\newbie\cpp_code\images\image-20211130151533476.png)

![image-20211130152226618](E:\newbie\cpp_code\images\image-20211130152226618.png)

这时就需要引出`this`关键字，它在成员函数相当于`Entity* ee = this;`，在成员函数中提供了访问成员属性的方式。要注意一点this是一个指针，因此再进行赋值时，要么使用`(*this).x`根据指针地址访问并存入，或者直接使用`this->x`，两者的作用是一样的。

```c++
class Entity
{
public:
	int x, y;

	Entity(int x, int y)
	{
		(*this).x = x;
		this->y = y;
        
        //delete this;  //不要在类中使用delete
	}
};
```

下面示例代码在VS 2019中报错？？？？？？？？？？？

```
#include <iostream>
#include <string>

//void PrintEntity(Entity* e);
void PrintEntity(const Entity& e);


class Entity
{
public:
	int x, y;

	Entity(int x, int y)
	{
		this->x = x;
		this->y = y;

		Entity& ee = *this;
		delete this;
		//PrintEntity(this);
		//PrintEntity(*this);
	}

	int GetX() const
	{
		const Entity& ee = *this;
		return x;
	}

};
/*
void PrintEntity(Entity* e)
{
	std::cout << "Pointer" << std::endl;
}
*/
void PrintEntity(const Entity& e)
{
	std::cout << "Reference" << std::endl;
}


int main()
{
	Entity e = Entity(1, 1);
	std::cin.get();
}
```



## 35. Object lifetime in C++

本节主要讲stack中变量的生命周期。

下面给出了一个示例：

![image-20211130173058864](E:\newbie\cpp_code\images\image-20211130173058864.png)

通过打印构造函数和析构函数，发现构造函数被调用了两次，即创建了个对象，但是只删除了一个对象，唯一的区别就是第二个对象使用了new关键字，被创建在了heap上需要手动进行清理或者直到程序被终止才会消失。

也就是说stack变量一旦离开他所属的域就会被释放掉。

```c++
#include <iostream>
#include <string>

int* CreateArray()
{
	int array[50];  //在stack中创建一个array，并返回指向那块stack内存的指针
	return array;  //尝试去返回指针指向的内存
}  //但是当代码执行到这一行，array所指向的那部分内存因为是属于stack的，所以在这里会被释放，导致实际上返回的是一块未初始化的空间

int main()
{
	int* a = CreateArray();  //导致至一行会报错？？？？？vs2019中不报错

	std::cin.get();

}
```

使用了new之后都必须手动释放空间吗？有没有自动的方法来实现呢

如下创建了一个局域指针（智能指针`ScopedPtr`）：

```c++
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
```

取代`Entity* e1 = new Entity();`而去使用`ScopedPtr`:

```c++
ScopedPtr e3(new Entity());
ScopedPtr e2 = new Entity();  //这么写也行但是它会触发隐式转换
```

用`ScopedPtr`创建的指针，当它跳出创建它的域时，也会被释放，这是因为他创建的指针在stack中，当跳出域这个指针要被释放时会调用他的析构函数，就会触发delete从而释放掉heap中的空间。在这种情况话即使使用了new，跳出域后也还是会释放掉相应的空间。

举一个最适当的应用：

我们想在获取程序运行的总耗时，正常写法是需要在程序运行前调用一次time，在程序性运行后在调用一次，计算时间差之并进行打印。那么我们就可以利用智能指针的便利性，创建一个time类（unique pointer）类似于上面的`ScopedPtr`，只需要在程序运行前调用一次，当程序运行结束后，它会自动调用析构函数，把计算时间差和打印写在构函数中，即跳出当前域的最后要执行的操作写在析构函数中，就能提高便利性。



## 36. Smart pointers in C++

对于new我们必须调用delete来释放相应的空间， Smart pointers就是可以用来自动化该流程的指针，使用了Smart pointers，当我们使用new时不需要再调用delete。有时甚至不用调用new。

Smart pointers实际上是真实raw pointer的一个wrapper，当我们创建于一个Smart pointers，让他来替我们调用new和delete

### 36.1 Unique pointer

Unique pointer是一个scope pointer，它会在程序跳出scope时被释放并调用delete。

Unique pointer不能被复制，一旦被复制，他们所指向的实际上是同一块内存，当其中一个指针被释放时就会释放掉那部分内存。

```c++
#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
	Entity() { std::cout << "Created Entity!" << std::endl; }
	~Entity() { std::cout << "Destroyed Entity!" << std::endl; }

	void Print() {}
};

int main()
{
	{
		std::unique_ptr<Entity> entity(new Entity());
		entity->Print();
	}
	std::cin.get();

}
```

使用下面代码来创建一个unique pointer，可以看到它只支持显式转换：

```c++
#include <memory>
std::unique_ptr<Entity> entity(new Entity());
```

更推荐的方法是：`std::unique_ptr<Entity> entity1 = std::make_unique<Entity>();`，这么些是为了保证exception safety，防止我们创建的unique pointer不够健壮，造成内存泄漏等。

尝试复制unique pointer报错：

![image-20211201100738345](E:\newbie\cpp_code\images\image-20211201100738345.png)

这是因为在源码中等号赋值和引用都被删除了。

![image-20211201100851190](E:\newbie\cpp_code\images\image-20211201100851190.png)

### 36.2 Shared pointer

智能指针使用引用计数的方法，他的运行逻辑是一直统计应用那个指针的个数，当用用个数为0时，指针所指向的空间被释放。也就是说先创建一个shared pointer，然后再创建一个shared pointer并复制第一个指针，那么指向同一块内存的指针就有两个了，当地一个指针被释放，引用的个数减去一，当作后一个指针被释放，引用的个数变为0，内存被释放。

shared pointer的定义：

```c++
//std::shared_ptr<Entity> sharedEntity(new Entity());
std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
```

坚决不能采用第一种方式来定义shared pointer，因为shared pointer会分配一个control block来存储引用个数，如果我们先new一个Entity然后再传给shared pointer，他需要重新进行分配，就会执行两次内存分配。如果直接使用第二种定义方式就能同时把两个内存都分配了，效率更高。

另外对于讨厌new关键字的开发者，shared pointer显然摒弃了new关键字，因为我们是直接调用std::make_shared

![image-20211201103237563](E:\newbie\cpp_code\images\image-20211201103237563.png)

### 36.3 Weak pointer

他有点像shared pointer，也可以进行复制，当我们把一个shared pointer复制给它时，他只会指向相同的内存，却不会使引用个数加一，也就是说它只能用来查看那个指针是否存在，但不能控制使得指针存在，即当weak pointer指针指向的shared pointer的所有正常引用都被清理了，只剩下weak pointer，那么这个指针同样会被释放掉。因此weak pointer不会影响shared pointer的生命周期。

当执行到第26行时，由于entity所有的引用都被清理了，即使weakEntity1是在域外，那所指向的空间同样被释放了，就会显示expired，即不能使用了。

![image-20211201104107030](E:\newbie\cpp_code\images\image-20211201104107030.png)

```c++
#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
	Entity() { std::cout << "Created Entity!" << std::endl; }
	~Entity() { std::cout << "Destroyed Entity!" << std::endl; }

	void Print() {}
};

int main()
{
	{
		std::shared_ptr<Entity> sharedEntity0;
		std::weak_ptr<Entity> weakEntity1;
		{
			std::unique_ptr<Entity> entity = std::make_unique<Entity>();
			entity->Print();

			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			//sharedEntity0 = sharedEntity;
			weakEntity1 = sharedEntity;
		}
	}
	std::cin.get();

}
```

当然我们可以询问一个weak pointer你是否还是有效的。

当我们想在heap中分配空间，但又不想操纵详细的生命周期和内存空间时，推荐使用智能指针，特殊的pointer的选择顺序：unique pointer优先于shared pointer。但他又不能完全替代new delete，当我们想操纵详细的生命周期和内存空间时当然还是使用new delete。



## 37. Copying and copy constructors in C++

Copying是指复制数据复制内存，也就是说他处理的结果是有两份内存。有时我们想要复制对象并修改其中内容，为了避免不必要的复制，因为复制是需要花费时间的，我们只是想读取他的内存并修改已经存在的对象。

### 37.1 Copying

```c++
#include <iostream>
#include <string>

struct Vector2 
{
	float x, y;
};

int main()
{
	int a = 2;
	int b = a;
	b = 3;

	Vector2 c = { 2, 3 };
	Vector2 d = c;

	Vector2* e = new Vector2();
	Vector2* f= e;
	f->x = 5;

	std::cin.get();
}
```

![image-20211201142725431](E:\newbie\cpp_code\images\image-20211201142725431.png)

只有e和f指向同一块内存，这是因为它复制的是指针。

总的来说，抛去引用当我们在写代码时，把一个变量赋值给另一个变量总是在copying，对于变量和指针变量的区别是，指针变量copying的是指针地址（以数值表示的内存地址）而不是实际的指针指向的内存。

### 37.2 浅拷贝

下面给出一个示例：创建一个String类，并支持它的输出。

```c++
#include <iostream>
#include <string>

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size];
		memcpy(m_Buffer, string, m_Size);
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

int main()
{
	String string = "Melissa";
	std::cout << string << std::endl;

	std::cin.get();
}
```

1. 查看输出结果发现，会有一连串位置符号，这是因为我们在存储字符时忘记存入终止符了。

   ![image-20211201144519281](E:\newbie\cpp_code\images\image-20211201144519281.png)

   一种方法是给string array多加1：

   ![image-20211201144735934](E:\newbie\cpp_code\images\image-20211201144735934.png)

   或者是直接给字符串为后面增加一个null。

   ![image-20211201145020981](E:\newbie\cpp_code\images\image-20211201145020981.png)

   这样处理后打印出来就是正常的。

2. 但是在上面的String类中使用new创建了新的字符串并未销毁，可能会造成内存泄漏，因此需要在类的析构函数中进行delete，完整的类如下：

   ```c++
   class String
   {
   private:
   	char* m_Buffer;
   	unsigned int m_Size;
   public:
   	String(const char* string)
   	{
   		m_Size = strlen(string);
   		m_Buffer = new char[m_Size];
   		memcpy(m_Buffer, string, m_Size);
   		m_Buffer[m_Size] = 0;
   	}
   	~String()
   	{
   		delete[] m_Buffer;
   	}
       char& operator[](unsigned int index)
   	{
   		return m_Buffer[index];
   	}
   
   	friend std::ostream& operator<<(std::ostream& stream, const String& string);
   };
   ```

3. 构建好了上面的类之后，假设我们想进行复制并修改string，主程序代码如下：

   ```c++
   int main()
   {
   	String string = "Melissa";
   	String second = string;
   
   	std::cout << string << std::endl;
   	std::cout << second << std::endl;
   
   	std::cin.get();
   }
   ```

   运行到程序结束时突然报错

   ![image-20211201145655364](E:\newbie\cpp_code\images\image-20211201145655364.png)

   分析：通过调试发现，string和second的m_Buffer的内存地址是相同的，其实这种复制方式是浅复制，也就是只复制了`char* m_Buffer;`的指针而非内存中的值。那么当程序运行结束时会按顺序分别调用string和second的析构函数，第一次调用是m_Buffer还存在，会delete m_Buffer，当第二次调用时就会发现他已经被释放了，delete就会报错。

   ![image-20211201145847048](E:\newbie\cpp_code\images\image-20211201145847048.png)

   也就是说，当我们修改第二个String时是会根据地址到到相应内存进行修改，导致两个变量都变了。

   ![image-20211201150927917](E:\newbie\cpp_code\images\image-20211201150927917.png)

   总的来说浅拷贝不会查看对象的内部成员或者查看指针指向的地址内容，并复制其中的所有东西，因此导致了上面的一系列问题。

### 37.3 深拷贝【创建copy constructor】

上面浅拷贝的方式有诸多的不便，我们希望在复制时不光复制指针，而且复制指针指向的内容，重新开辟一块空间来存储内容，并把这块内存的地址留给新的指针。

也就是说深拷贝会完整的复制整个对象，具体的操作就是创建一个copy constructor。

`Copy Constructor`是一个构造函数，当该对象被复制时会自动调用该`复制构造函数`，它是在类中接受一个同类型常量引用的函数：

```c++
String(const String& other)
	:m_Buffer(other.m_Buffer), m_Size(other.m_Size)
{
}
```

或者还可以使用`memcpy`函数：

```c++
String(const String& other)
{
    memcpy(this, &other, sizeof(String));
}
```

如果我们不想这个类被复制呢可以直接将`Copy Constructor`删掉：

```c++
String(const String& other) = delete;
```

![image-20211201154857991](E:\newbie\cpp_code\images\image-20211201154857991.png)

类成员有指针变量就得写深拷贝。

```c++
class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size];
		memcpy(m_Buffer, string, m_Size);  //这里不确定string是否包含null
		m_Buffer[m_Size] = 0;  //就手动在字符串后添加null
	}

	~String()
	{
		delete[] m_Buffer;
	}

	String(const String& other)
		:m_Size(other.m_Size)
	{
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);  //在这里就可以直接使用m_Size+1因为我们确定other是包含null的
	}
	
	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};
```

完善代码封装PrintString方法

```c++
#include <iostream>
#include <string>

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}

	~String()
	{
		delete[] m_Buffer;
	}

	String(const String& other)
		:m_Size(other.m_Size)
	{
		std::cout << "Copied string!" << std::endl;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}
	
	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

void PrintString(String string)
{
	std::cout << string << std::endl;
}

int main()
{
	String string = "Melissa";
	String second = string;

	second[1] = 'a';

	PrintString(string);
	PrintString(second);

	std::cin.get();
}
```

打印结果如下：发现string不光被显式复制了一次，还在我们不知道的情况下被复制了两次。

![image-20211201172450122](E:\newbie\cpp_code\images\image-20211201172450122.png)

其实是又`PrintString`导致的，它接收的参数是String本身，在接收到外部变量会先全部复制一份出来，然后再用这部分副本进行处理，导致上面多次调用copy constructor。为了说明`PrintString`话把所有参数都复制一份，给它增加一个参数，再次运行代码就会发现，copy constructor总共被多用了两次，而`PrintString`函数有两个参数，正好说明了这一点。

![image-20211201175703586](E:\newbie\cpp_code\images\image-20211201175703586.png)

为了避免这种我们只是使用这个变量但是并不修改它时额外复制导致的效率降低和内存占用，建议使用引用`const String&`

```c++
void PrintString(const String& string, const String& string2)
{
	std::cout << string << std::endl;
}
```

此时会发现程序输出结果只调用了一次copy constructor。

![image-20211201180036376](E:\newbie\cpp_code\images\image-20211201180036376.png)

建议：在写函数时能使用const reference就使用，我们可以在函数内部决定到底要不要去复制这个对象，但是不要直接传入对象的的副本（这是自动的），太蠢了。const reference能够介绍大量没有的复制





