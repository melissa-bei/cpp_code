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











