C++

## 24. Array in C++

```c++
int example[5];
```

int表示存储的类型，方括号中表示Array的长度，即该array能够存储5个整数，通过索引进行访问。

```c++
example[0] = 2;
```

因为c++的索引是从0开始的，长度为5的array的索引分别为[0，1，2，3，4]，如果尝试访问-1，5就会违规，在debug模式中会报错，但是在release模式下就回去直接访问不属于它的内存。

如果想去访问并设置array中的每个值，可以通过for循环来实现。

在debug模式中查看内存，可以发现`example`实际上是一个内存地址，是一个整形指针。当访问`example[4] = 2;`时，实际上是从example开始，再加上4*4(int的字节数)也就是16个字节来找到索引为4的数的。

为了验证example是一个内存地址，可以定义一个整形指针来指向example，并使用指针移动来替换array的索引操作：

```c++
#include <iostream>


int main()
{
	int example[5];
	int* ptr = example;

	for (int i = 0; i < 5; i++)
	{
		example[i] = 2;
	}

	example[2] = 5;
	*(ptr + 2) = 6;  //与example[2]指向的时相同的内存

	std::cin.get();
}
```

![image-20211124165322607](E:\newbie\cpp_code\images\image-20211124165322607.png)

第15行代码中只写了指针偏移2，但在实际的内存中偏移了8个字节，这是取决于指针的类型，整型字节就要给偏移数乘以4，2*4即是8个字节。

如果非要按字节来处理就需要通过强制转换，将int指针转为只占一个字节的char指针，同时需要给指针偏移8，拿到了起始点地址之后还需要再强制转换回int指针就能实现原来的效果，它其实就是夺银的实际作用。

```c++
*(int*)((char*)ptr + 8) = 6;
```

---

我们还可以在heap中创建array，这要用到new字段。下面两行代码开辟的空间以及是养伤都是一样的，唯一的区别就是生命周期。example在stack中，当运行到它所属的方法或类结束后就被销毁掉，而another是在heap上创建了一个array，它会一直存在直到我们手动销毁。

```c++
int example[5];
int* another = new int[5];
```

删除heap在中创建的array

```c++
delete[] another;
```

**new既然这么麻烦为什么还非要使用它呢？**

这都是由生命周期决定的，如果我们想让函数返回一个结果到其他位置时就必须使用new来分配内存，或者把结果存在某个地址中，如果不这么做，把结果存在stack中，函数结束该内存就会被释放掉。如果想要返回一个在函数中新创建的内存数据，就必须使用new关键字。

```c++
#include <iostream>

class Entity
{
public:
	int example[5];

	Entity()
	{
		for (int i = 0; i < 5; i++)
		{
			example[i] = 2;
		}
	}
};

class Entity2
{
public:
	int* another = new int[5];

	Entity2()
	{
		for (int i = 0; i < 5; i++)
		{
			another[i] = 2;
		}
	}
};


int main()
{
	Entity e;
	Entity2 e2;

	std::cin.get();
}
```



### Extra

我们是没有办法直接访问array的大小的，比如通过如下代码我们在heap中开辟了能存储5个int值的内存空间，但是是无法通过`example->size()`来获取该array的大小的。

```c++
int* example = new int[5];
```

反过来想，我们在使用delete字段释放array占用的内存空间时解析器肯定时需要知道array占用了多少空间的，也就是说是有一些方法能够获取到array的长度的：（但是是不可靠的）

```c++
int a[5];
sizeof(a)  //获取占用的总字节数
sizeof(a) / sizeof(int)  //总字节数除以数据类型占用的字节数，就能得到array的长度
```
下面给出一个示例来说明上面的计算方法为什么不可靠：

```c++
#include <iostream>

class Entity
{
public:
	int example[5];

	Entity()
	{
		int size = sizeof(example);  //20 bytes
		int count = sizeof(example) / sizeof(int);  //5
		for (int i = 0; i < 5; i++)
		{
			example[i] = 2;
		}
	}
};

class Entity2
{
public:
	int* another = new int[5];

	Entity2()
	{
		int size = sizeof(another);  //4
		int count = sizeof(another) / sizeof(int);  //1
		for (int i = 0; i < 5; i++)
		{
			another[i] = 2;
		}
	}
};


int main()
{
	Entity e;
	Entity2 e2;

	std::cin.get();
}
```

上述代码运行中，26、27行的size和count分别为4和1，与正确的20和5不一样，这是因为another本身是一个int指针，而不是array本身，因此只是统计了第一个元素并未计算整个array。

**在C++中，只能通过自行定义函数来记录array的长。**

```c++
static const int exampleSize = 5;
int example[exampleSize];
```

定义一个array时，方括号中的长度必须是一个已经编译好的常数，因此必须加上static，防止报错。<u>还有一切其他方法可以解决报错问题，如constaexpr要求变量必须是静态的，以后可能会讲到。</u>

类的完整定义如下：

```c++
class Entity
{
public:
	static const int exampleSize = 5;
	int example[exampleSize];

	Entity()
	{
		int size = sizeof(example);
		std::cout << size << std::endl;
		int count = sizeof(example) / sizeof(int);
		std::cout << count << std::endl;
		for (int i = 0; i < exampleSize; i++)
		{
			example[i] = 2;
		}
	}
};
```

另外在C++11中可以直接使用标准库array

```c++
#include <array>

std::array<int, 5> another;
another.size();  //访问array大小
```



## 25. How Strings work in  C++

Strings就是由一系列字符组成的array，字符包括数字、字母、符号等可以打印出来的东西。

> 大量复杂的引言用来介绍char、string、英文字符与其它语言字符、utf8、utf16、常见字符、扩展字符等等，以后可能会讲到，这里就只讲解最简单的一个字节的字符。

通过如下方式定义一个字符串

```
const char* name = "C++";
```

使用const标识符是想使得name是不可修改的，因为字符串是存储在一块固定大小的内存，如果我们想要存入一个更长的字符串，就需要分配新的内存来进行存储。

char 指针意味着他不是一个堆式分配，因为没有用到new来分配，肯定不能通过delete来进行删除。

因为定义为const因此不能通过索引来修改其中的某个字符串，通过查看运行时内存可以看到转换成ASCII码值的字符串。在www.AsciiTable.com来查看内存中的值实际表示的字符是什么。

![image-20211125112155683](E:\newbie\cpp_code\images\image-20211125112155683.png)

仔细观察，在我们存入的三个字符之后还有一个`00`，它是**null字符**，表示我们如何去判断一个string什么时候结束。

- **注意：c++中，单引号表示单个字符char类型；双引号表示多个字符，是char指针类型（char array），注意不是string**。

### 25.1 char, char* 和C++中字符串的基本处理方式

我们使用下面代码分别来创建两个字符串，并进行输出，

```c++
#include <iostream>

int main()
{
	const char* name = "Melissa";  //使用const标识符是想使得name是不可修改的，
	std::cout << name << std::endl;
	char name2[7] = { 'M', 'e', 'l', 'i', 's', 's', 'a' };
	std::cout << name2 << std::endl;
	std::cin.get();
}
```

会发现name2打印出了一系列奇怪的字符，查看对应内存可以发现，通过赋值每个字符的方式不会生成null结束符，因此会在读取到null字符之后才结束。

![image-20211125114040916](E:\newbie\cpp_code\images\image-20211125114040916.png)

![image-20211125114218708](E:\newbie\cpp_code\images\image-20211125114218708.png)

要使它不出错就需要给name2增加一个长度，并赋予结束字符

```c++
char name2[8] = { 'M', 'e', 'l', 'i', 's', 's', 'a', 0 };
char name2[8] = { 'M', 'e', 'l', 'i', 's', 's', 'a', '\0' };
```

### 25.2 string

c++中有一个基本的string还有一个标准库的string

iostream里面由string，但是如果我们想要打印string就必须要include <string>

```c++
#include <string>  //重载<<符号，使它可以接收string

std::string name3 = "Melissa";
```

可以通过`.size()`来获取string的size，而对于char[]和char指针都需要使用`strlen`等来获取，就比较麻烦。

**注意：**

1. 还有一些处理，比如我们想把两个字符串拼接起来，不能直接使用`+`，因为这相当于要把两个char array拼接起来。

   

   ```c++
   std::string name3 = "Melissa" + "go";
   ```

   - **双引号在C++中表示char array。**

   要想实现这一功能，可以将它拆分成两行，

   ```c++
   std::string name3 = "Melissa";
   name3 += "go";
   ```

   ![image-20211125141706880](E:\newbie\cpp_code\images\image-20211125141706880.png)

   或者把第一个字符串改为string类型，即通过string的重载+拼接字符串

   ```c++
   std::string name4 = std::string("Melissa") + "go";
   ```

2. string API的使用[string - C++ Reference (cplusplus.com)](https://www.cplusplus.com/reference/string/string/)

   ```c++
   bool contains = name3.find("sa") != std::string::npos;  //在name3中查找 sa，并返回它起点的位置
   ```

3. 在函数中传递string

   我不会这么做是因为，它是把string copy进来，如果我们在函数内部直接对输入进来的string进行操作，是不会影响原来的string的。它是在heap中开辟一块空间来存储复制已经有的数据的，这比较慢，如果我们要传递一个string，而且它是只读的，最好是使用const引用来进行传递的。

   其中`&`表示不进行复制，直接引用，`const`表示不可修改。

   ```c++
   void PrintString(const std::string& string)
   {
   	std::cout << string << std::endl;
   }
   ```

### 25.3 Strings Literals in C++

字符串就是双引号引出的一串字符，它由一串字符和最后的结束符（null 字符）组成，告诉编译器这个字符串结束了。

#### 25.3.1 普通的字符串

- 在定义一个字符串的时候，字符串的长度必须大于等于字符个数+1，这是因为最后还有一个结束符，否分就会报错，如下图所示：

  ![image-20211125150430592](E:\newbie\cpp_code\images\image-20211125150430592.png)

- 当长度比实际字符个数+1大时，多出来的空间都被赋值为null字符。

  ![image-20211125150851372](E:\newbie\cpp_code\images\image-20211125150851372.png)

- 如果我们在字符串中不小心加入了`\0`，在读到它时就会提前结束。使用`strlen`获取到的是实际的字符串长度而不是我们开辟的空间的长度。

  ![image-20211125151144239](E:\newbie\cpp_code\images\image-20211125151144239.png)

  可以注意到，上面我们使用了const来定义字符串，为的是防止我们去修改字符串，如果尝试去通过索引赋值修改其中的字符时就会报错。

  ![image-20211125151752055](E:\newbie\cpp_code\images\image-20211125151752055.png)

- **那可不可以去掉const来修改呢？**

  答案是否定的。理论上来说，我们是定义了一个char指针类型的变量来存储字符串，通过字符串索引的方式可以访问到相应的内存，但是因为**字符串是存储在只读的空间中**，是不能修改的。有些编辑器会像下图一样报错，有些会提示未定义操作，有些则不会甚至可以编译成功，我们不能依靠它来进行判断。

  ![image-20211125151958224](E:\newbie\cpp_code\images\image-20211125151958224.png)

  编译后查看源码，会发现字符串被存储在CONST SEGMENT空间中

  ![image-20211125152952048](E:\newbie\cpp_code\images\image-20211125152952048.png)

  使用HxD工具查看编译出的21_Strings.exe文件，会发现该字符串是存储在我们的二进制文件中的，当我们引用时，会引用一个const data segment，它不允许我们进行修改。

  ![image-20211125154302979](E:\newbie\cpp_code\images\image-20211125154302979.png)
  
  即使某些编译器在编译时对于给字符串中字符赋值不报错，但是实际上也是不起作用的。
  
  如果非要去修改字符串的内容，就需要通过array来定义（下面第一行）而不是指针来定义（下面第二行），千万不要这么去编程。
  
  ```c++
  char* name = "Melissa";
  char name2[] = "Melissa";
  
  char name8[] = "Melissa";
  std::cout << name8 << std::endl;
  name8[2] = '0';
  std::cout << name8 << std::endl;
  ```
  
  ![image-20211125161052431](E:\newbie\cpp_code\images\image-20211125161052431.png)
  
  通常来说，c++直接给定一个字符串就是指const的，但是如果非要赋给char*不加const的话，就要给字符串进行强制类型转换，但是进行复制同样会报错。
  
  ```c++
  char* name7 = (char*)"Melissa";
  ```
  
  ![image-20211125161612611](E:\newbie\cpp_code\images\image-20211125161612611.png)
  
  这几个示例是想说明指针型字符串不能进行修改，一定是const。

#### 25.3.2 wild 字符串

使用`wchar_t`类型来定义wild字符串，还需要给字符串前加上`L`来表示后面的字符是由wild字符组成的。

```c++
const wchar_t* name9 = L"Melissa";
```

一些其他类型字符串：

```c++
const wchar_t* name9 = L"Melissa";  //16 bits
const char16_t* name10 = u"Melissa";  //16 bits, utf16
const char32_t* name10 = U"Melissa";  //32 bits, utf32
const char* name11 = u8"Melissa";  //8 bits, utf8
```

`wchar_t`和`char16_t`看起来都是两个字节，有什么区别呢？

`wchar_t`所占位数个数都是理论上的，但是实际占用多少取决于编译器，可能是1，可能是2，也可能是4，通常情况下是2或4，在windows中是2，linux中是4。如果为了确保是2个字节建议使用`char16_t`。

#### Extra

- 其他要注意的就是，我们常在处理url时需要进行拼接操作，因此在c++14之后添加了`std::string_literals`ti工了一些便于操作的函数。

  原本我们对于两个字符串相加是不能直接处理的（下面第一行），上一届提供的方法是使用std::string进行重载（下面第二行）。除此之外，我们还可以调用std::string_literals中的方法，在第一个字符串后面加一个**`s`**进行重载。

  ```c++
  //std::string  name11 = "melissa" + "go";  //会报错
  std::string name4 = std::string("Melissa") + "go";
  
  using namespace std::string_literals;
  std::string  name11 = "melissa"s + "go";
  ```

- **`R`**重载

  需要在字符串前添加`R`在双引号内部添加小括号，就可以避免字符串太长换行导致的拼接，打印出来的字符串也是带换行符的。

  ```c++
  std::string  name12 = R"(melissa
  go
  wo)";
  ```

  ![image-20211125165415793](E:\newbie\cpp_code\images\image-20211125165415793.png)

  也可以不要任何拼接符，直接换行写字符串

  ```c++
  std::string  name15 = "melissa"
  		"go"
  		"wo";
  ```

  它打印出来的结果字符串是连着的，即没有换行符，如果需要出现在新的一行就需要手动添加`\n`，因此才需要用R重载去替代

  ![image-20211125165553007](E:\newbie\cpp_code\images\image-20211125165553007.png)

  ![image-20211125165802494](E:\newbie\cpp_code\images\image-20211125165802494.png)

  这部分内容是方便我们在代码中去写入大段的文本。

- **字符串永远被存储在只读的内存空间中**

  即使我们通过`char name8[] = "Melissa";`创建了可修改的字符串，查看编译的源代码发现，该字符串还是处在const segment中，那么他是如何实现字符串的修改呢？

  之前以指针方式创建的字符串，进行修改时，我们实际上是要去修改那个const内存，当然是不行的，而通过现在array的创建方式，在进行修改时，会先去找到那个const字符串，然后重新创建一本变量来存储相同的内容，然后再进行修改。



## 26. CONST inC++

C++中的const好像实际并没有做什么处理，只是方便了开发者去阅读，使代码可读性更高，相当于一种承诺，保证所定义的变量是常量。

### 26.1 CONST in Pointer

给出下面一个例子，对于一个指针我们可以修改它的内容，也可以修改它的地址。

```c++
#include <iostream>
#include <string>

int main()
{
	const int MAX_AGE = 90;  //定义一个常量

	int* a = new int;

	*a = 2;  //修改指针指向的内容
	std::cout << *a << std::endl;
	a = (int*)&MAX_AGE;  //修改指向的地址
	std::cout << *a << std::endl;

	std::cin.get();
}
```

根据**内容**和**地址**可修改性，指针可以分为以下四种：

1. 普通的指针

   内容和地址都可修改，如上述代码所示。

2. **指针常量**【<u>无法修改地址</u>】

   如果在定义指针变量时候，**指针变量前用const修饰**，被定义的指针变量就变成了一个指针类型的常变量，**指针类型的常变量**简称为指针常量。

   格式：`数据类型  *  const  指针变量=变量名;`

   ```c++
   char * const p="ABCDEF";
   
   p=NULL;//错误，指针常量不能再改变
   p="1234";//错误
   p=(char *)q;//错误
   *P='B'；//正确
   ```

   修饰符const与指针变量紧邻，说明指针变量不允许修改，既然指针变量的值不能修改，所以**一定要在定义的时候给定初值（指向一个确定存在的地方）**。**即指向的内存地址不能修改。但是空间中的内容可以修改。**

   ![image-20211125182026076](E:\newbie\cpp_code\images\image-20211125182026076.png)

3. **常量指针**【<u>无法修改内容</u>】

   如果在定义指针变量的时候，**数据类型前用const修饰**，被定义的指针变量就是指向常量的指针变量，**指向<u>常量</u>的<u>指针变量</u>**称为常量指针.

   格式：`const 数据类型  *指针变量=变量名;`，或者`数据类型  const  * 指针变量=变量名;`，**要求就是const必须出现在`*`之前。**

   ```c++
   const char *P="ABCDEF";
   
   *P='1';//错误，视图更改指针指向的值
   p[1]='1';//错误
   p=NULL;//正确，视图修改指针的位置，而不是修改指针指向的内容
   ```

   定义一个常量指针后，指针指向的值就不能被改变，即不能通过指针变量直接更改指针指向的值。**即指向的内存空间不能修改。但是可以指向别的地址。**

   ![image-20211125182054485](E:\newbie\cpp_code\images\image-20211125182054485.png)

4. **常指针常量**【<u>无法修改内容和地址</u>】

   格式：`const  数据类型 * const 指针变量=变量名;`或者`数据类型 const  *const 指针变量=变量名;`

   ```c++
   char *q;
   const char * const p="ABCDEF";//定义了一个常量常指针
   
   q=p;//错误，试图讲一个常指针赋值给非常指针
   p=q;//错误，试图修改指针常量的值，如1
   *p='1'；//错误，试图修改指针指向的值，如2
   p[1]='1';//错误，如2
   p=NULL；//错误，如1
   ```

   **指针不能改变，指针指向的值也不能改变。**

- 总的来说，**const在`*`之前和之后表示不同含义，但是在`数据类型`前后表示相同含义。**

![image-20211125184213286](E:\newbie\cpp_code\images\image-20211125184213286.png)

### 26.2 CONST in method（only works in class）

在类中，方法名后面的const表示该方法不能修改实际的class成员。定义一个Entity类：

```c++
class Entity
{
private:
	int m_X, m_Y;
public:
	int GetX()
	{ 
		return m_X;
	}
	int GetY()
	{
		return m_Y;
	}
};
```

给`GetY`方法后加上const约束，是表示该方法不能修改类的成员属性，否则会报错

![image-20211125185119903](E:\newbie\cpp_code\images\image-20211125185119903.png)

如果定义的属性是指针类型，还可以像下面一样操作，它的作用与上面定义为整型变量并只在方法后加上const一样。

- 第一个const表示不能修改指针指向空间的内容；
- 第二个const表示不能修改指针指向的地址；
- 第三个const表示该方法不能修改类中的成员属性。

![image-20211125185306716](E:\newbie\cpp_code\images\image-20211125185306716.png)

需要注意的是`int m_X, m_Y;`这个写法只是使得第一个变量`m_X`变成了指针，第二个变量还是整型，从下图中`GetX`和`GetY`两个方法的返回值就能看出来。

![image-20211125190138494](E:\newbie\cpp_code\images\image-20211125190138494.png)

如果想在一行定义中使得所有变量都是指针时，必须给每个变量前都加上`*`。

```C++
class Entity
{
private:
	int * m_X,* m_Y, * m_Z;
public:
	int* GetX()
	{ 
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
```

### **疑问：**没搞清楚需要再看看

**观察如下代码，我们`GetX`方法本身并不进行修改类的成员属性，只是返回它的值，也就是说该方法的内容就说明了它不会修改m_X的值，那还有必要加 const 在后面吗？**

```c++
class Entity
{
private:
	int m_X;
public:
	int GetX() const
	{ 
		return m_X;
	}
};
```

答案是肯定的，const绝对保证了类成员属性不被修改。下面举例说明为什么必须加const来保证`m_X`不被修改

通常在定义一个方法时，为了不进行复制，会传入引用变量，对于引用变量我们不能修改它的值，但是可以去修改指向的地址。如果这么去定义了函数，那么对于这个类对象就只能去调用他的常方法（即不修改成员属性的方法），但如果想要调用的方法不是const就会出错。？？？？？？？？？？？？？

![image-20211125192305831](E:\newbie\cpp_code\images\image-20211125192305831.png)

### 26.3 const与mutable关键字

反过来，如果我们已经定义了某个方法为const，但是为了调试或者一些其他原因非要去修改它，那也是有办法的。

这就引出了`mutable`关键字，给类成员属性加上mutable关键字，就能够在const方法中修改成员属性。

![image-20211126100640857](E:\newbie\cpp_code\images\image-20211126100640857.png)



## 27. mutable关键字

mutable有两种用法，一个是和const一起使用，在26.3中已经提到过。另一种用法就是在lambda。

### 27.1 mutable关键字与const

如果我们在说到某个const变量是mutable的，也就是说它是常量但是是可以修改的。

![image-20211126113146284](E:\newbie\cpp_code\images\image-20211126113146284.png)

定义一个Entity类包含一个私有成员属性，并有一个常函数来返回它的值。如果我们实例化一个Entity的对象并限制为const，那么它就不能调用Entity中的非const函数，如上图所示报错。为了使得一些其他定义能够访问到GetName方法就必须将它定义为常方法，因为它本质上就是只返回m_Name，并未修改成员属性，功能就是一个常函数。

下面举个例子，为了进行调试，我们想要统计GetName常方法被调用了多少次，定义一个私有成员属性m_DebugCount来记录调试次数，并在每次调用GetName时进行自增。

这时可以发现一个矛盾的地方，**为了保证const Entity能够调用GetName方法，需要将该方法定义为常方法，但是同时它就不能修改类中的成员属性**，无法实现向我们想要的效果。

![image-20211126113818145](E:\newbie\cpp_code\images\image-20211126113818145.png)

有一个方法是将`int m_DebugCount = 0;`移到类外去，但是这回是代码比较混乱，因为这个变量只是需要在类中起作用就行，放在类外如果不小心被修改可能会改变。这时就需要用到mutable关键字来解决：

```c++
#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
	mutable int m_DebugCount = 0;  //使得该变量在常方法中是可修改的
public:
	const std::string& GetName() const
	{
		m_DebugCount++;
		return m_Name;
	}
};

int main()
{
	const Entity e;
	e.GetName();

	std::cin.get();
}
```

### 27.2 mutable关键字与lambda【不常用】

#### 27.2.1 lambda表达式

在 c + + 11 及更高版本中，lambda 表达式（通常称为 " *lambda*"）是一种定义匿名函数对象的简便方法， (*关闭*) 在调用的位置或作为自变量传递给函数的位置。 通常，lambda 用于封装传递到算法或异步函数的几行代码。

 lambda 的组成部分如下：

![Lambda 表达式的结构元素的图例。](E:\newbie\cpp_code\images\images_lambda)

1. **捕获子句 (也称为 c + + 规范中的 *引导* 。 )**
2. ***参数列表* 可有可无. (也称为 *lambda 声明符*)**
3. ***可变规范* 可有可无.**
4. ***异常规范* 可有可无.**
5. ***尾随-返回类型* 可有可无.**
6. ***lambda 体*。**

##### 1.Capture子句

它指定捕获的变量以及捕获是通过值还是通过引用来捕获。

- 具有 "and" 符号 (`&`) 前缀的变量通过引用访问。

![image-20211126141418637](E:\newbie\cpp_code\images\image-20211126141418637.png)

- 空 capture 子句 `[ ]` 指示 lambda 表达式的主体不访问封闭范围中的变量。

![image-20211126141247747](E:\newbie\cpp_code\images\image-20211126141247747.png)

`[=]` 这意味着 lambda 体中引用的<u>**任何**外部变量</u>是**通过值捕获**的。

`[&]` 这意味着 lambda 体中引用的<u>**任何**外部变量</u>是**通过引用捕获**的。

可以使用**默认捕获模式**，然后**为特定变量显式指定相反的模式**。 例如，如果 lambda 体通过引用访问外部变量 `total` 并通过值访问外部变量 `factor`，则以下 capture 子句等效：

```c++
[&total, factor]
[factor, &total]
[&, factor]
[factor, &]
[=, &total]
[&total, =]
```

需要注意的是：

- **使用捕获默认值时只捕获 lambda 主体中提到的变量。**
- *如果捕获子句包含一个捕获-默认值** `&` ，**则该捕获子句捕获中的任何标识符都不能具有该格式** `&identifier` 。 同样，如果捕获子句包括捕获默认值 `=` ，则该捕获子句的捕获不能具有格式 `=identifier` 。 **标识符或 `this` 在捕获子句中不能出现多次。**
- 下面的代码段演示了一些示例：

```c++
struct S { void f(int i); };

void S::f(int i) {
    [&, i]{};      // OK
    [&, &i]{};     // ERROR: i preceded by & when & is the default
    [=, this]{};   // ERROR: this when = is the default
    [=, *this]{ }; // OK: captures this by value. See below.
    [i, i]{};      // ERROR: i repeated
}
```

若要在类成员函数的主体中使用 lambda 表达式，请将 **`this`** 指针传递给捕获子句，以提供对封闭类的成员函数和数据成员的访问。

> 当你使用 capture 子句时，建议你记住这些要点，尤其是在将 lambda 用于多线程时：
>
> - 引用捕获可用于修改外部变量，但值捕获不能。 (**`mutable`** 允许修改副本，而不是原始副本。 )
> - 引用捕获会反映外部变量的更新，而值捕获则不会。
> - 引用捕获引入生存期依赖项，而值捕获却没有生存期依赖项。 当 lambda 异步运行时，这一点尤其重要。 如果在异步 lambda 中按引用捕获本地，则在运行 lambda 时，可以轻松地实现本地。 你的代码在运行时可能会导致访问冲突。

##### 通用捕获 (C++14)

在 C++14 中，可在 Capture 子句中引入并初始化新的变量，而无需使这些变量存在于 lambda 函数的封闭范围内。 初始化可以任何任意表达式表示；且将从该表达式生成的类型推导新变量的类型。 利用此功能，您可以捕获仅移动变量 (如 `std::unique_ptr` 来自周围范围的) 并在 lambda 中使用它们。

```c++
pNums = make_unique<vector<int>>(nums);
//...
      auto a = [ptr = move(pNums)]()
        {
           // use ptr
        };
```

##### **2.参数列表**

Lambda 既可以捕获变量，也可以接受输入参数。 标准语法) (*lambda 声明符* 的参数列表是可选的，在大多数情况中，与函数的参数列表类似。

```c++
auto y = [] (int first, int second)
{
    return first + second;
};
```

在 **c + + 14** 中，如果参数类型为泛型，则可以使用 **`auto`** 关键字作为类型说明符。 此关键字指示编译器将函数调用运算符作为模板来创建。 参数列表中的每个实例 **`auto`** 都等效于不同的类型参数。

```c++
auto y = [] (auto first, auto second)
{
    return first + second;
};
```

##### **3.可变规范**

通常，lambda 的函数调用运算符是按值常数值，但使用 **`mutable`** 关键字会取消此操作。它不会生成可变的数据成员。 该 **`mutable`** 规范使 lambda 表达式的主体可以修改通过值捕获的变量。

##### 4.异常规范

您可以使用 **`noexcept`** 异常规范来指示 lambda 表达式不会引发任何异常。 与普通函数一样，如果 lambda 表达式声明 **`noexcept`** 异常规范且 lambda 体引发异常，Microsoft c + + 编译器将生成警告 C4297，如下所示：

```cpp
// throw_lambda_expression.cpp
// compile with: /W4 /EHsc
int main() // C4297 expected
{
   []() noexcept { throw 5; }();
}
```

##### 5.返回类型

将自动推导 Lambda 表达式的返回类型。 [`auto`](https://docs.microsoft.com/zh-cn/cpp/cpp/auto-cpp?view=msvc-170)除非指定 *尾随返回类型*，否则不需要使用关键字。 *尾随返回类型* 类似于普通函数或成员函数的返回类型部分。 但是，返回类型必须跟在参数列表的后面，并且必须在返回类型前面包含尾随返回类型关键字 **`->`** 。

如果 lambda 主体只包含一个返回语句，则可以省略 lambda 表达式的返回类型部分。 如果表达式不返回值，则为或。 如果 lambda 体包含单个返回语句，编译器将从返回表达式的类型推导返回类型。 否则，编译器会将返回类型推导为 **`void`** 。 请考虑以下示例代码片段，它们阐释了这一原则：

```c++
auto x1 = [](int i){ return i; }; // OK: return type is int
auto x2 = []{ return{ 1, 2 }; };  // ERROR: return type is void, deducing
                                  // return type from braced-init-list isn't valid
```



## 28. Member initializer lists in C++【建议使用】

Member initializer lists 是在构造器里初始化类对象的方法。

下面定义了一个类有两个参数不同的构造函数，

```c++
class Entity
{
private:
	std::string m_Name;
public:
	Entity()
	{
		m_Name = "Unknown";
	}
	Entity(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& GetName() const { return m_Name; }
};
```

可以使用成员初始化列表`:m_Name("Unknown"), m_Score(0)`来替代构造器中的内容。该列表以`:`开始，后面跟随成员属性，括号中是需要赋给它的值，如果有多个成员属性需要初始化，以`,`分隔。

```c++
class Entity
{
private:
	std::string m_Name;
	int m_Score;
public:
	Entity()
		:m_Name("Unknown"), m_Score(0)
	{}
	Entity(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& GetName() const { return m_Name; }
};
```

**要注意的是多个属性的初始化顺序必须和成员属性声明的顺序相同**，否则像下面这样反过来，还是先给`m_Name`赋值

```c++
class Entity
{
private:
	std::string m_Name;
	int m_Score;
public:
	Entity()
		:m_Score(0), m_Name("Unknown")
	{}
	Entity(const std::string& name)
		:m_Name(name)
	{}

	const std::string& GetName() const { return m_Name; }
};
```

上面说明了Member initializer lists的用法其实很简单，他和结构体也没什么区别，那么问题是，为什么要用他呢？

一个原因是多个成员属性的初始化，会增加代码的行数，使这部分占了大头而忽略了之后可能执行的其他初始化步骤，可以是代码更简洁，提高可读性。

还有一个区别是有可能会把一个对象初始化两次，一次在声明，还有一次在初始化赋值

```c++
#include <iostream>
#include <string>


class Example
{
public:
	Example()
	{
		std::cout << "Created Entity!" << std::endl;
	}
	Example(int x)
	{
		std::cout << "Created Entity! with " << x << "!" << std::endl;
	}
};

class Entity
{
private:
	std::string m_Name;
	Example m_Example;  //第一次创建Example对象
public:
	Entity()
	{
		m_Name = "Unknown";
		m_Example = Example(8);  //创建第二个Example对象并覆盖第一个
	}
	Entity(const std::string& name)
		:m_Name(name)
	{}

	const std::string& GetName() const { return m_Name; }
};

int main()
{
	Entity e0;

	std::cin.get();
}
```

输出结果如下：

![image-20211129103907556](E:\newbie\cpp_code\images\image-20211129103907556.png)

创建的第一个对象完全没有被使用直接被丢掉了。

解决办法：一是把`:m_Example(Example(8))`的定义放在成员初始化列表中，二是在成员初始化列表中直接把8赋给`m_Example`，即`:m_Example(8)`

```c++
#include <iostream>
#include <string>


class Example
{
public:
	Example()
	{
		std::cout << "Created Entity!" << std::endl;
	}
	Example(int x)
	{
		std::cout << "Created Entity! with " << x << "!" << std::endl;
	}
};

class Entity
{
private:
	std::string m_Name;
	Example m_Example;
public:
	Entity()
		: m_Example(Example(8))
	{
		m_Name = "Unknown";
	}
	Entity(const std::string& name)
		:m_Name(name)
	{}

	const std::string& GetName() const { return m_Name; }
};

int main()
{
	Entity e0;

	std::cin.get();
}
```

![image-20211129104158254](E:\newbie\cpp_code\images\image-20211129104158254.png)

理论上来说，这个开辟空间上的区别只有在类中才会出现，对于一些基本类型只有初始化时才会定义，之前只会声明，但是还是建议无论是哪种类型都是用成员初始化列表。



## 29. Ternary Operator in C++

三目运算符`?:`是if语句的另一种写法。

下面是一个if else语句的示例，if else语句占用四行已经比较简洁了，但是如果使用`?:`还可以更简洁。

```c++
#include <iostream>
#include <string>

static int s_Level = 1;
static int s_Speed = 2;

int main()
{
	if (s_Level > 5)
		s_Speed = 10;
	else
		s_Speed = 5;
    
    

	std::cin.get();
}
```

下面用一行代码来完成上述功能，不仅使代码看起来整洁了，而且会快一点点。

```c++
s_Speed = s_Level > 5 ? 10 : 5;
```

使用格式：`条件 ? 条件为True ： 条件为False`

下面代码能够实现，`s_Level`小于5给`s_Speed`赋值5，大于5小于10赋值10，大于0 赋值15。但是不建议套用

```c++
s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;
```



## 30. How to create instantiate objects in C++

前面学习了如何创建一个类，那么他只要不是纯静态类，我们就需要去进行实例化生成对象来使用。

实例化方式有两种，它们之间的区别在于在哪里开辟内存空间。就算我们定义一个完全空的类，它也至少占用一个字节的空间。

stack对象有自动控制寿命的权力，它们的寿命由声明他们的域决定，一旦离开相应的域，它们对应的内存就会被释放，因为当那个域运行结束，stack把相应的内存pop出去，pop出的这部分内存都会被释放。

heap就不一样了，一旦在heap上创建了对象，分配了内存空间，它会一直存在在heap中，直到我们不需要那部分内存需要进行释放时，手动释放那部分内存。

调试下面代码：

```c++
#include <iostream>
#include <string>

using String = std::string;  //为什么不使用using std::以后会讲到

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
		Entity entity0;  //只要有构造函数这一行就不会报错
		std::cout << entity0.GetName() << std::endl;
		Entity entity1("Melissa");
		Entity entity2 = Entity("Melissa");  //这是c++中最可控且最快的实例化方式

		e = &entity1;
		std::cin.get();
	}
}
```

会发现通过`Entity entity1("Melissa");`创建的对象，当执行到27行时，e指针指向了entity1的地址，里面存着Melissa，

![image-20211129153401502](E:\newbie\cpp_code\images\image-20211129153401502.png)

执行到29行时，跳出了entity1所属于的域，他相应的内从空间就被释放了，那么e指向的那个地址，内容也就是空的。
![image-20211129153635463](E:\newbie\cpp_code\images\image-20211129153635463.png)

这种情况下，如果我们想在域之外还能使用在域中定义那部分内存就需要在heap中时分配内存空间。还有一个建议使用heap内存的情况，当创建的对象特别多或者类特别大的时候，建议分配到heap中，因为stack空间是很有限的，一般是1-2个megabyte（取决于开发平台和编译器）。

在heap中时分配内存空间：必须使用new关键字，必须返回Entity指针，它携带的是存放新对象的地址

```c++
Entity* entity3 = new Entity("Melissa");
```

---

### Leftover

1. **从Java或者C#转战C++的开发者，通常会在C++中到处都是用new关键字，但是不建议，这么做有两个原因，以后会讲到：**
   1. 分配到heap中比stack更耗时
   2. **需要手动去释放分配的空间**

   ![image-20211129161435720](E:\newbie\cpp_code\images\image-20211129161435720.png)

   ![image-20211129161557878](E:\newbie\cpp_code\images\image-20211129161557878.png)

2. 这里还提到了一个知识点，`->`的含义以后会讲到

   ```c++
   Entity* entity3 = new Entity("Melissa");
   std::cout << entity3->GetName() << std::endl;
   std::cout << (*entity3).GetName() << std::endl;
   ```

### 总结

在创建一个实例时，首先分析他所属的类是不是很大，他的对象是不是很多，以及我是否要准阔空是他的生命周期，如果答案都是否定的，则建议在stack中分配内存，既简单又方便而且速度快，否则建议在heap中分配内存。



## 31. The new keyword in C++

每当我们使用new关键字时，编译器需要在内存中去找连续的满足我们要求的内存空间来进行使用，虽然机器本身会有一个list存储了所有的空闲的内存地址，但是这依旧是需要耗时。

```c++
int main()
{
	int a = 2;  //在stack中分配4 bytes的空间
	int* b = new int;  //在heap中分配4 bytes的空间
    int* c = new int[5];  //在heap中分配长度为5，每个占4 bytes的空间
    
    Entity* e = new Entity();

	std::cin.get();
}
```

### 31.1 与malloc的关系

要注意的一个点是，new关键字不仅是在heap中开辟空间，还在实例化时调用了构造函数。通常使用New关键字会调用**`malloc()`**，他的功能就是memory allocate，括号里提供的参数是字节数，也就是说以下两行代码开辟的空间大小是一样的：唯一的区别就是前者会调用Entity类的构造函数，后者只是开辟了和它同样大小的内存空间。

```c++
Entity* e = new Entity();
```

```c++
Entity* e = (Entity*)malloc(sizeof(Entity));
```

> void pointer就是一个没有类型的指针

### 31.2 delete

使用了new关键字来创建对象，就必须使用delete来释放他开辟的空间。

创建时没有`[]` 直接调用`delete 对象名`，创建时使用了`[50]`就必须调用`delete[] b`来释放内存

### 31.3 New 的另一种用法`new()`，也叫做Placement New

`new()`这种形式可以有开发者去决定新的对象到底放在那里，在括号中写的是已经开辟好内存的变量的地址（必须是指针），比如下面第五行的写法。

它的作用是新实例化一个Entity对象放放在已经开辟好的空间（指定的地址）中，这种情况下，不会真的去重新分配空间，而是只调用类的构造函数，在那个指定的空间中进行初始化

```c++
int a = 2;
int* b = new int;
int* c = new int[50];
	
Entity* e = new(c) Entity();
```



### 32. Implicit conversion and the explicit keyword in c++

c++中的隐式转换和显式关键字 

### 32.1 Implicit conversion 隐式转换

定义一个Entity类，有两个构造函数，分别接受std string和int作为参数，

```c++
#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
	int m_Age;
public:
	Entity(const std::string& name)
		:m_Name(name), m_Age(-1) {}
	Entity(int age)
		:m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity& entity)
{
}

int main()
{
	Entity a("Melissa");
	Entity b = std::string("Melissa");
	Entity c(22);
	Entity d = 22;
	PrintEntity(22);
	PrintEntity(Entity("Melissa"));
	std::cin.get();
}
```

通常我们通过`Entity a("Melissa");`和`Entity c(22);`来分别调用这两个构造函数，在c++中还有一种写法，是用等号，如`Entity d = 22;`，这里因为给定的22是整数会自动调用接受int为参数的构造函数。但是当我们尝试用等号来接收Melissa时发现报错如下：

![image-20211130100922522](E:\newbie\cpp_code\images\image-20211130100922522.png)

这里的问题是因为在一个语句中只允许做一次隐式转换。上面的赋值过程主要经历两个步骤，首因为Melissa本身是包含7个字符的const char array 而不是std string ，必须先进行一次类型转换，然后再调用接收std string的构造函数，这里涉及了两次操作Implicit conversion无法处理就会报错。当我们手动进行类型转换如下面的写法，就能解决这个问题，可以把字符串转为std string类型，或者直接把melissa包含在std::string或Entity中：

```c++
Entity b = std::string("Melissa");
PrintEntity(Entity("Melissa"));
```

注意：虽然可以使用隐式转换但是不建议这么做。

### 32.2 explicit

指定了类的构造函数为`explicit`，也就是说它只能进行显示调用，隐式转换隐式调用都不起作用，相应的直接用等号去赋值的方法就会报错。

![image-20211130103714342](E:\newbie\cpp_code\images\image-20211130103714342.png)

通常在数学库中会使用explicit，当我们不想任何时候都把数字转化为向量，以保证代码更安全或什么的。但是不建议使用的经常使用，比如当我们构建级别较低的wapper时，希望进行手动操作或者处理意外地cast导致的bug。



## 33. Operators and operator overloding in c++

Operators就是我们再代码中写出来用来执行某种操作的符号。operator overloding允许我们去自定义会修改operator在程序中的作用，这个功能在Java中不支持，C#支持一部分，而C++是完全支持的。

总的来说，operator就是函数，它不是通过给定函数名的方式，而是直接给定了一个符号。大多数情况下使用operator能够使代码看起来更简单。

下面给出了一个基本示例，定义了一个包含两个float变量的`Vector2`，定义一个二维坐标点`position`、二维的速度`speed`、二维的提速向量`powerup`来实现位置的移动，为此需要给`Vector2`添加`加`和`乘`的函数来实现基本的提速和位移.

```c++
#include <iostream>
#include <string>

struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}
};

int main()
{
	Vector2 position(4.0f, 4.0f);  //位置
	Vector2 speed(0.5f, 1.5f);  //速度
	Vector2 powerup(1.1f, 1.1f);  //提速后速率

	Vector2 result = position.Add(speed.Multiply(powerup));

	std::cin.get();
}
```

但是第28行的写法还是过于繁琐，如果能用简单的`+`和`*`来进行处理就显得简洁的多，如下面一行代码所示：

```c++
Vector2 result = position + speed * powerup;
```

我们也想直接用操作符来进行Veator2的加减乘除操作，并满足运算规律，比如乘除级别高于加减等，最后再返回Vector2。

比如，重载操作符+，用它调用Add方法：

```c++
struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 operator+(const Vector2& other) const  //重载操作符+，用它调用Add方法
	{
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}
};
```

也可以把Add方法的操作直接在重载操作符中执行，然后Add方法再去调用操作符：

```c++
struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return operator+(other);
        //return *this + other;
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}
};
```

两种方式中，作者更建议第一种，因为给其他的开发者提供了两种可选的用法。最终结构体如下：

```c++
struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}
};
```

当我们想输出的时候会发现，std::cout并不能输出Vector2类型的数据，会报错如下：

![image-20211130113944919](E:\newbie\cpp_code\images\image-20211130113944919.png)

就需要我们去重载`<<`：

```c++
std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << other.X << ", " << other.Y;
	return stream;
}
```

该重载需要接收一个std::ostream，也就是`std::cout`，然后接收一个Veator2，使用stream把Veator2的两个成员属性输出，最后返回std::ostream，也就是`std::cout`。

完整代码如下：

```c++
#include <iostream>
#include <string>

struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << other.X << ", " << other.Y;
	return stream;
}

int main()
{
	Vector2 position(4.0f, 4.0f);  //位置
	Vector2 speed(0.5f, 1.5f);  //速度
	Vector2 powerup(1.1f, 1.1f);  //提速后速率

	Vector2 result = position.Add(speed.Multiply(powerup));
	Vector2 result2 = position + speed * powerup;

	std::cout << result << std::endl;

	std::cin.get();
}
```

输出结果如下图：

![image-20211130114627160](E:\newbie\cpp_code\images\image-20211130114627160.png)

**注意：即使可以去重载操作符，但还是不建议这么做，会影响代码阅读效果。**

我们重载的`<<`操作符有点像在Java或C#中会写的ToString方法，这就是c++的特色之处，我们不光能定义函数，还可以重载操作符。

另外一点，c++支持`==`操作符，Java不支持，在Java中必须写`equals`来进行比较，下面举例来重载`==`和`!=`：

```c++
#include <iostream>
#include <string>

struct Vector2
{
	float X, Y;

	Vector2(float x, float y)
		:X(x), Y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}

	bool operator==(const Vector2& other) const
	{
		return X == other.X && Y == other.Y;
	}

	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
		//return !operator==(other);  //不建议这么写，很奇怪
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << other.X << ", " << other.Y;
	return stream;
}

int main()
{
	Vector2 position(4.0f, 4.0f);  //位置
	Vector2 speed(0.5f, 1.5f);  //速度
	Vector2 powerup(1.1f, 1.1f);  //提速后速率

	Vector2 result = position.Add(speed.Multiply(powerup));
	Vector2 result2 = position + speed * powerup;

	std::cout << result << std::endl;

	if (result == result2)
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}

	std::cin.get();
}
```
