C++

## 1. Welcome(HelloWorld)

> 【BV1VJ411M7WR】

> 如果在C++中写垃圾代码，C++绝对比C#和Java慢，因为后者语言运行时会优化很多东西而C++不会



## 2. Setup

```C++
#include <iostream>

int main()
{
	std::cout << "Hello world!" << std::endl;
	std::cin.get();
}
```



## 3. How C++ works

- **预处理指令**，即以 `#` 开头的代码。当编译器收到一个源文件时，所做的第一件事就是预处理所有的预处理指令。
- **`#include <>`** 是找到一个文件，上面代码中是找到叫 `iostream` 的文件，该文件里的所内容都会被复制粘贴到目前这个文件里。
- **`<file>`** include的这些文件一般被称为 header file（头文件）。
- **`cout`** include  `iostream` 文件是因为我们代码中用到了 `cout`，它是我们能够打印东西到 console （控制台）
- **`main` 函数**，每个 C++ 程序都有类似这个的东西，被称为入口点（entry point），也就是程序的入口。`main` 函数返回类型是 `int`，但是我们并没有从主函数中返回任何值，这是`main` 函数在没有返回的情况下默认返回0。
- `<<` 其实是重载符号

---

> 所有 .cpp 文件都会被编译，而头文件不会。因为在头文件 include 到当前文件时候进行了编译。
>
> 每一个 .cpp 文件时分别进行编译的，编译后生成一个 object 文件，在windows中扩展名时`.obj`。当有了一个个 .obj 文件后，需要通过某种方式将他们连接起来，这就是 `linker`(连接器)的用武之处了。

----

我们在**单独的.cpp文件中定义**方法，**在main.cpp中调用**该方法时需要先声明，即向该文件承诺有相应的方法存在，以保证linker工作时不会出错，这必须一致，否则找不到的话会报出linker error。如果有明明错误，单独编译main.cpp时没有问题的，只有在生成时才会报错

![image-20211103095214622](E:\newbie\cpp_code\images\image-20211103095214622.png)



## 4. How C++ compiler works

>  c++编译器唯一要做的就是把文本变为中继格式 `.obj`。
>
> 项目里的每个.cpp文件都会被编译成一个.obj，这些**`.cpp文件`**也叫做 **translation unity**（编译单元）。
>
> 即一个 **translation unity**会被编译器编译为一个 `object`文件

***<u>在c++中文件没有含义</u>***。比如 java要求class名必须与文件名相同，而且文件夹结构也得跟package一样。**但是c++没有文件这种东西，文件只是用来给编译器提供源码的某种方法。**编译器会自动根据文件类型处理文件，如.cpp、.c、.h。

> 在c++中一个cpp文件中include其他cpp文件是很常见的，本质上时将多个cpp文件组合成一个大的cpp文件里面包含了很多个文件。如果我们编译那一个大的cpp文件，也就是一个translation unity，则只会得到一个obj。
>
> 当且仅当我们的cpp文件中从不互相include的话，则一个cpp文件就是一个translation unity，每一个也会产生一个obj。

### 4.1 理解header文件用法的一个神奇的例子

1. 新建Math.cpp文件，并写入如下代码：

```c++
int Multiply(int a, int b)
{
	int result = a + b;
	return result;
#include "EndBrace.h"  //这一步就是简单粗暴的打开EndBrace.h，然后把里面的内容粘贴在当前文件中，即就能彻底理解header文件到底是怎么用的了。
```

2. 再新建EndBrace.h文件，添加如下内容：

```c++
}
```

3. 编译项目没有出错，也就证明了 include header文件就是直接将头文件复制粘贴到当前文件中。

### 4.2 另一个让编译器输出文档，里面包含preprocessor执行的结果

点击项目-->属性-->c++-->预处理器-->预处理到文件-->选择是-->应用

![image-20211103105029356](E:\newbie\cpp_code\images\image-20211103105029356.png)

重新编译当前文件得到`.i`文件。**此选项将取消编译，因此不会生成.obj文件。**

![image-20211103105242167](E:\newbie\cpp_code\images\image-20211103105242167.png)

```c++
#define INTEGER int  //查找前者用后者替换，不用加分号
```

![image-20211103110346229](E:\newbie\cpp_code\images\image-20211103110346229.png)

可以看到编译结果是一样的没有改变。

### 4.3 #if`if预处理语句可以让我们根据特定条件包含或者剔除代码

```c++
#if 1
int Multiply(int a, int b)
{
	int result = a + b;
	return result;
}
#endif
```

编译结果如下：

![image-20211103105242167](E:\newbie\cpp_code\images\image-20211103105242167.png)

```c++
#if 0
int Multiply(int a, int b)
{
	int result = a + b;
	return result;
}
#endif
```

编译结果如下：

![image-20211103111635420](E:\newbie\cpp_code\images\image-20211103111635420.png)

点击项目-->属性-->c++-->输出文件-->汇编程序输出-->仅有程序集的列表-->应用，就可以得到.obj文件的可读版本。

![image-20211103114643556](E:\newbie\cpp_code\images\image-20211103114643556.png)

可以看到有一个名为Multiply的代码段，这就是我们运行函数时cpu执行的真正指令。

![image-20211103115144873](E:\newbie\cpp_code\images\image-20211103114857146.png)

可以看到在63行将eax赋值给result，因为我们自定义了一个result变量，但是这个是非必要的。也就是说我们在写代码时要注意优化，不然底层就会有很大一部分时间在做无用功。

如下，去掉result，直接返回a和b的成绩，指令就简便了一些。

```c++
int Multiply(int a, int b)
{
	return a * b;
}
```

![image-20211103115358711](C:\Users\Melissa\AppData\Roaming\Typora\typora-user-images\image-20211103115358711.png)

这些代码看起来这么长是因为我们实在debug环境下进行编译的，而debug环境不进行任何优化，以确保代码尽可能冗长以及尽可能易于debug。

点击项目-->属性-->c++-->优化-->优化-->最大优化速度-->应用。

![image-20211103120005633](E:\newbie\cpp_code\images\image-20211103120005633.png)

![image-20211103120218718](E:\newbie\cpp_code\images\image-20211103120218718.png)

![image-20211103120339884](E:\newbie\cpp_code\images\image-20211103120339884.png)

设置优化后，代码缩减到47行。

![image-20211103120449735](E:\newbie\cpp_code\images\image-20211103120449735.png)

如果直接输入如下代码：

```c++
int Multiply()
{
	return 5 * 2;
}
```

真实指令也很简单，就是把10 mov到eax寄存器。而且还把把5*2简化成10，因为没有必要对两个常熟在运行时计算，这就是所谓的constant folding（常量折叠），任何之都会、可以在编译时计算出来。

![image-20211103120726720](E:\newbie\cpp_code\images\image-20211103120726720.png)

增加一个Log函数，并调用，看看其编译出来的结果。

```c++
const char* Log(const char* message)
{
	return message;
}

int Multiply(int a, int b)
{
	Log("Multiply");
	return a * b;
}
```

![image-20211103121330510](E:\newbie\cpp_code\images\image-20211103121330510.png)

调用函数时，编辑器就会产生一个call指令。

![image-20211103121547255](E:\newbie\cpp_code\images\image-20211103121547255.png)

## 5. How C++ linker works(HelloWorld2)

linking是从c++源码到可执行二进制时的一个过程。linking主要的工作是找到每个符号和函数的位置，并将它们链接在一起。

> 编译（`ctrl`+`F7`）只会编译，而生成（build`F5`）先编译然后链接。

- error的错误类型也提示了我们错误出现在什么阶段。比如，`C2143: 语法错误`中**C**开头表示错误发生在**编译**阶段，`LNK1561: entry point must be defined`中**LNK**开头表示错误发生在**linking**阶段。
- 如果生成对象是.exe文件时，则必须有一个entry point。

### 5.1 函数名的重要性

例如，有如下Log.cpp文件专门存放和日志相关的代码。

```c++
#include <iostream>

void Log(const char* message)
{
	std::cout << message << std::endl;
}
```

Math.cpp专门执行计算。

```c++
#include <iostream>

void Log(const char* message);

int Multiply(int a, int b)
{
	Log("Multiply");
	return a * b;
}

int main() 
{
	//std::cout << Multiply(5, 8) << std::endl;
	std::cin.get();
}
```

但是当我们不小心写错了Log.cpp文件中的Log，写成了Logr，单独编译Math.cpp是不会报错的。因为我们在Math.cpp中声明告诉主函数保证会有名为Log的函数存在的，至于函数到底存不存在不是编译过程要考虑的。

然后当我们生成项目时，报错提示linker无法解析外部符号Log，它在Multiply中被调用。

![image-20211103150615814](E:\newbie\cpp_code\images\image-20211103150615814.png)

- **如果注释掉上面的第7行，生成项目不会报错的，相当于没有调用过Log。**

- **但是，如果保留第7行注释13行，还会报同样的错误。这是因为我们虽然没有在当前文件中调用Multiply也即没有调用Log，但是有可能在其他文件中调用，因此linker也需要去链接它。**

- 除非在注释13行的同时告诉linker，Multiply只在当前文件中使用，linker也就不用去链接它。该方法就是给Multiply方法加上**`static`**的修饰词，即**静态变量函数**。

  ```c++
  #include <iostream>
  
  void Log(const char* message);
  
  static int Multiply(int a, int b)
  {
  	Log("Multiply");
  	return a * b;
  }
  
  int main() 
  {
  	//std::cout << Multiply(5, 8) << std::endl;
  	std::cin.get();
  }
  ```

### 5.2 返回类型的重要性

如果把Log.cpp中Log的返回类型改成int，则同样无法linking，因为linker会去寻找一个名为Log、且返回为void的函数。

```c++
#include <iostream>

int Log(const char* message)
{
	std::cout << message << std::endl;
	return 0;
}
```

![image-20211103153728984](E:\newbie\cpp_code\images\image-20211103153728984.png)

### 5.3 参数的重要性

如果给Log.cpp中Log的参数增加一个int类型level，则同样无法linking，因为linker会去寻找一个名为Log、且返回为void、同时只接受一个char为输入参数的函数。

```c++
#include <iostream>

int Log(const char* message, int level)
{
	std::cout << message << std::endl;
	return 0;
}
```

![image-20211103153728984](E:\newbie\cpp_code\images\image-20211103153728984.png)

---

### 5.4 小结

**以上三部分说明了，在连接过程中，函数名、返回类型、参数个数类型三个重要元素缺一不可，都必须被严格满足。**不要求的是，<u>定义和声明中参数的名称可以不同</u>。

当有两个函数的上述三部分都完全相同，linker也会报错。因为linker不知道该链接哪个。这种情况在同一个文件中发生我们是很容易察觉的，但通常这种问题会出现在不同的文件中，就不容易发现了。

例如Log.cpp文件如下，一眼就能看出错误。

```c++
#include <iostream>

void Log(const char* message)
{
	std::cout << message << std::endl;
}

void Log(const char* message)
{
	std::cout << message << std::endl;
}
```

我们执意去编译就会出现如下错。

![image-20211103155204723](E:\newbie\cpp_code\images\image-20211103155204723.png)

但如果在Log.cpp和Main.cpp中分别包含有一个完全一样的Log函数，这就会报出一个linking error，提醒我们Log被重复定义了，而且linker不知道应该链接哪个？

Log.cpp

```c++
#include <iostream>

void Log(const char* message)
{
	std::cout << message << std::endl;
}
```

Math.cpp

```c++
#include <iostream>

void Log(const char* message);

void Log(const char* message)
{
	std::cout << message << std::endl;
}

int Multiply(int a, int b)
{
	Log("Multiply");
	return a * b;
}

int main() 
{
	//std::cout << Multiply(5, 8) << std::endl;
	std::cin.get();
}
```

![image-20211103155901026](E:\newbie\cpp_code\images\image-20211103155901026.png)

### 5.5 linker报出重复定义的较难识别的场景

这种问题出现的频率比我们想象的要高，以下举几个会出现这种情况的例子

先定义一个Log.h，

```c++
#pragma once

void Log(const char* message)
{
	std::cout << message << std::endl;
}
```

然后在Logc.cpp中导入Log.h，

```c++
#include <iostream>
#include "Log.h"

void InitLog()
{
	Log("Initialized Log");
}
```

最后在Math.cpp中导入Log.h，

```c++
#include <iostream>
#include "Log.h"

void Log(const char* message);

int Multiply(int a, int b)
{
	Log("Multiply");
	return a * b;
}

int main() 
{
	//std::cout << Multiply(5, 8) << std::endl;
	std::cin.get();
}
```

编译过程正常不报错，生成过程就会报重复定义Log函数的错。

---

**疑问：**

**我们明明只在`Log.h`中定义了一次Log函数，为什么还会报重复定义的错误呢？**

**分析：**

**这就涉及到了include的工作原理。include其实是将头文件中的代码赋值粘贴到当前文件中，那么当我们分别在`Log.cpp`和`Math.cpp`中分别include了`Log.h`也就相当于在这两个文件中分别定义了一次Log函数。**

**如何解决：**

1. 一种方法是，**我们在`Log.h`文件中把Log函数定义为`static`，也就是这个log函数在链接时只应发生在该文件内部。**也就是说当这个Log函数在Log.cpp中和Math.cpp中，只会对该文件内部有效。即Log.cpp中和Math.cpp这两个文件分别会持有个人版本的Log函数，而且他们对于其他的.obj文件时不可见的。

   Log.h内容如下：

   ```c++
   #pragma once
   
   static void Log(const char* message)
   {
   	std::cout << message << std::endl;
   }
   ```

2. 另一种方法是，**让Log函数变成`inline`，他的意思是把函数的身体拿过来取代调用。**

   ```c++
   #pragma once
   
   inline void Log(const char* message)
   {
   	std::cout << message << std::endl;
   }
   ```

   也就是说，如下的调用，

   ```c++
   void InitLog()
   {
   	Log("Initialized Log");
   }
   ```

   实际上会变成：

   ```c++
   void InitLog()
   {
       std::cout << "Initialized Log" << std::endl;
   }
   ```

3. 作者会采用的方法是把Log函数的定义移动到一个**translation unity**中。会出现上述问题是因为Log函数被包含在两个translation unity中。

   具体操作方法：把Log定义部分移动到Log.cpp中，然后再Log.h中只留下声明。三个文件内容分别如下：

   Log.h

   ```c++
   #pragma once
   
   void Log(const char* message);
   ```

   Logc.cpp

   ```c++
   #include <iostream>
   #include "Log.h"
   
   void Log(const char* message)
   {
   	std::cout << message << std::endl;
   }
   
   void InitLog()
   {
   	Log("Initialized Log");
   }
   ```

   Math.cpp

   ```c++
   #include <iostream>
   #include "Log.h"
   
   void Log(const char* message);
   
   int Multiply(int a, int b)
   {
   	Log("Multiply");
   	return a * b;
   }
   
   int main() 
   {
   	std::cout << Multiply(5, 8) << std::endl;
   	std::cin.get();
   }
   ```

   即Log函数的定义只出现在Log.cpp中，在Log.h和Math.cpp中都只是进行了声明调用。

## 6. Variables in C++(HelloWorld3)

C++中给定了一些原始数据类型，这些数据类型基本上构成了我们在程序中存储的任何类型的数据的基础，每种数据类型都有特定的目的，但是我们并不一定非要将它用于那个目的。

**在C++中，不同的变量类型之间的唯一区别就是大小。即这个变量占用多少内存**

| 数据类型 | 长度 | 注意|
| -------- | ---- | ---- |
| char     | 1 bytes |char通常用于存储字符，即50和'A'（其实也是数字，是它对应的ASCII码值）都可以|
| short | 2 bytes ||
| int   | 4 bytes ||
| long  | 4 bytes ||
| long long | 8 bytes ||
| float |4 bytes||
| double |8 bytes||
| long double |||
| bool |1 bytes|**虽然它本身只占一位（bits），但是寻址不能寻到每个bit，只能寻址到bytes。因此我们无法创建一个大小只有1 bit的变量类型。**|

### 6.1 char

如果我们给**char类型**赋值**数字65**，当**char类型传入cout是都会被当作字符对待**。

```c++
#include <iostream>

int main()
{
	char a = 'A';
	std::cout << a << std::endl;
	a = 65;
	std::cout << a << std::endl;
	std::cin.get();
}
```

### 6.2 short

同理，如果我们给**short类型**赋值**字符’A‘**，当**short类型传入cout是都会被当作数字对待**。

```c++
#include <iostream>

int main()
{
	short a = 'A';
	std::cout << a << std::endl;
	a = 65;
	std::cout << a << std::endl;
	std::cin.get();
}
```

### 6.3 float and double

如果想存一个浮点数，可以使用float和double，但是下面代码可以看出虽然我们定义的是float类型，但是实际存储的却是double类型。

![image-20211104113611576](E:\newbie\cpp_code\images\image-20211104113611576.png)

那么应该如何区分这两个类型呢？解决方法就是在float变量后面加上一个**`f`**或者**`F`**。

![image-20211104113948925](E:\newbie\cpp_code\images\image-20211104113948925.png)

### 6.4 bool

0表示false，其他任何数字都表示true，即给bool类型变量赋任何除0以外的值，cout打印出来的都是1。

![image-20211104114500462](E:\newbie\cpp_code\images\image-20211104114500462.png)

**虽然它本身只占一位（bits），但是寻址不能寻到每个bit，只能寻址到bytes。因此我们无法创建一个大小只有1 bit的变量类型。**

> 一种高级的用法是把8个bool组成一个byte，即每一个bool本身还是只占一个bit。

### 6.5 sizeof

用来获取变量的字节数

```c++
#include <iostream>

int main()
{
	char a = 5;
	std::cout << sizeof(a) << std::endl;
	short b = 5;
	std::cout << sizeof(b) << std::endl;
	int c = 5;
	std::cout << sizeof(c) << std::endl;
	long d = 5;
	std::cout << sizeof(d) << std::endl;
	float e = 5.5f;
	std::cout << sizeof(e) << std::endl;
	double f = 5.5;
	std::cout << sizeof(f) << std::endl;
	bool g = 5;
	std::cout << sizeof(g) << std::endl;
}
```

打印 1 2 4 4 4 8 1。

### 6.6 其他类型

**指针**：在类型旁边加上一个`*`。

**引用**：在类型旁边加上一个`&`。

## 7. Functions in C++

函数是编写的代码块，被设计用来执行某个特定的任务。后面讲到class时，那些代码块被称为methods，Functions之的书某种不属于某个class的东西。

> 分离出函数，很大程度上是为了**防止代码重复**。

比如分离惩罚逻辑过程。多次调用Multiply方法并打印结果

```c++
#include <iostream>

int Multiply(int a, int b)
{
	return a * b;
}

int main()
{
	int result = Multiply(3, 2);
	std::cout << result << std::endl;
	int result2 = Multiply(8, 5);
	std::cout << result2 << std::endl;
	int result3 = Multiply(90, 45);
	std::cout << result3 << std::endl;

	std::cout << "HelloWorld" << std::endl;
	std::cin.get();
}
```

可以看出调用方法和打印语句同样被书写了很多次，因此也可以封装程一个函数MultiplyAndLog。

```c++
#include <iostream>

int Multiply(int a, int b)
{
	return a * b;
}

void MultiplyAndLog(int a, int b)
{
	int result = Multiply(a, b);
	std::cout << result << std::endl;
}


int main()
{
	MultiplyAndLog(3, 2);
	MultiplyAndLog(8, 5);
	MultiplyAndLog(90, 45);

	std::cout << "HelloWorld" << std::endl;
	std::cin.get();
}
```

我们应该把代码拆分成许多函数。但是也不能太过，因为那样会导致代码更慢，每当我们调用一次函数，编辑器就会产生一个call命令，也就是说程序运行中为了调用函数，我们需要为这个函数创建一整个stack frame（栈框架），也就是说我们得把参数之类的东西堆入栈中，还需要把一个返回地址的东西放到栈中，然后跳到程序的某个不同部分，一执行函数里的指令，再把结果push，因为需要返回给调用函数之前的地方。这里指令在内存中跳来跳去都要消耗时间。**但是这些是建立在便一九七决定保留函数作为函数，而不是内联（inline）它。**

- 函数如果定义必须返回某个类型的值，则最后必须返回这个值。

  ![image-20211104162801530](E:\newbie\cpp_code\images\image-20211104162801530.png)

- 有趣的是这一设定只在DEBUG模式下报错，在Release模式下编译不会报错。

  ![image-20211104162707318](E:\newbie\cpp_code\images\image-20211104162707318.png)

  但是如果我们实际那这个返回值去做处理的话，会得到未定义行为报错。

函数会被拆分为定义和声明，声明通常会存在head file中，而定义会写在translation unity里。

## 8. C++ header files

在C++基础中，头文件传统上是用来声明某些函数类型，以便于可以用于整个程序中。有声明这部分是为了让程序知道有这么个函数存在，比如我们在一个文件中创建函数，然后想要在另一个文件中使用，当我们尝试编译那个文件时C++肾实质都不会知道那个函数的存在，所以我们需要一个共同的地方来存放生命，而非定义（函数只能被定义一次）。

Log.cpp

```c++
void Log(const char* message);  //声明有这个函数存在

void InitLog()
{
	Log("Initializing Log");
}
```

Main.cpp

```c++
#include <iostream>

void Log(const char* message)
{
	std::cout << message << std::endl;
}


int main()
{
	Log("HelloWorld");
	std::cin.get();
}
```

上述示例中，通过声明`void Log(const char* message)`告诉程序有这个函数，项目可以生成。

但是如果我想在其他文件中也调用这个函数呢？是需要把这个声明到处复制粘贴吗？

这里给出一个简单的方法，**头文件！！！！！！！！！**

头文件的原理就是复制粘贴头文件中的代码到include的文件中。修改代码如下：

Log.h

```c++
#pragma once

void Log(const char* message);
```

log.cpp

```c++
#include <iostream>
#include "Log.h"

void Log(const char* message);

void InitLog()
{
	Log("Initializing Log");
}
```

Main.cpp

```c++
#include <iostream>
#include "Log.h"  //虽然在当前文件中已经包含了Log函数的定义，但是复制粘贴Log的声明也是不会报错

void Log(const char* message)
{
	std::cout << message << std::endl;
}

int main()
{
	Log("HelloWorld");
	std::cin.get();
}
```

### #pragma once（推荐）

每个头文件在编译之前被C++预处理器计算，pragma其实是一个被输入到编辑器或者预处理器的指令，告诉他们只include这个文件一次。

**`pragma once`**被称作**头文件保护符**`header guard`，它的功能是**防止我们把单个头文件多次include到一个single translation unity中**。注意他不能防止我们把头文件到处include，只是防止在单一翻译单元中多次include。

比较好的方法来示意这种情况是在头文件中创建一个struct，并注释掉pragma once

Log.h

```c++
//#pragma once

void Log(const char* message);
void InitLog();

struct Player {};
```

log.cpp

```c++
#include <iostream>
#include "Log.h"
#include "Log.h"  //重复include Log.h

void Log(const char* message)
{
	std::cout << message << std::endl;
}

void InitLog()
{
	Log("Initializing Log");
}

```

Main.cpp

```c++
#include <iostream>
#include "Log.h"

int main()
{
	Log("HelloWorld");
	std::cin.get();
}
```

就会产生如此下错误

![image-20211104173857500](E:\newbie\cpp_code\images\image-20211104173857500.png)

这里的错误就显而易见了。但实际情况往往更复杂，比如我们创建一个`Common.h` include了`Log.h`，然后在Log.cpp中分别include 这两个头文件，同样注释`Log.h`中的`#pragma once`.

Common.h

```c++
#pragma once

#include "Log.h"
```

Log.h

```c++
//#pragma once

void Log(const char* message);
void InitLog();

struct Player {};
```

Log.cpp

```c++
#include <iostream>
#include "Common.h"
#include "Log.h"

void Log(const char* message)
{
	std::cout << message << std::endl;
}

void InitLog()
{
	Log("Initializing Log");
}
```

同样会报“struct”类型重定义的错误。取消注释`#pragma once`代码就能正常生了。

### #ifndef

与`#pragma once`作用基本相同，它的功能是先检查`_LOG_H`是否存在，如果没有被定义，把结构体中的代码include 到编译里；如果被定义了则下面的代码都不会被include，会全部被禁用。

Log.h

```c++
#ifndef _LOG_H
#define _LOG_H

void Log(const char* message);
void InitLog();

struct Player {};
#endif
```

### include<> 和 include ""

当我们编译时有两种方式告诉编译器include的路径，分别是绝对路径和相对路径。

- **`include <>`**即绝对路径，是让编译器在所有**include路径（需要进行设置的）**里去搜索这个文件。

- **`include ""`**即相对路径，用于include文件存在于当前文件的相对位置的情况。

也就是说尖括号只用于编译器里的include路径，而双引号可以用于所有情况。

**注意：**

`#include <iostream>`中，iostream是没有后缀的看起来不像一个文件，这是写标准库的人设计的用于区分C标准库和C++标准库

- C标准库：有.h后缀
- C++标准库：没有后缀



## 9. How to debug C++ in VS

- 断点
- 查看内存

只有在debug模式下加断点才是有意义的。

计算器-->三杠-->程序员-->就能计算2、8、10、16进制

查看内存：

![20211104182423](E:\newbie\cpp_code\images\image-20211104182423.jpg)

通过`&`+变量名就能查询到变量的内存地址。

## 10. Conditions and branches in C++(if statements)

if 语句和if-else语句

当我们跑代码时，会有对实际条件情况的比较，还有取决于比较结果的分支。

>  if 语句分支实际上就是比较条件、跳转到内存中的其他部分然后执行指令，意味着，如果我们的语句和分支分布在内存距离较远的地方，并且当我们打算写一些搞笑的代码是，就有可能不去使用if语句。实际上很多优化过的代码会尤其避免分支结构，避免比较，因为那么做会让代码变慢。

> 本节最后我们会看一些将分支结构去除的优化示例。

![image-20211105094532915](E:\newbie\cpp_code\images\image-20211105094532915.png)

![image-20211105094717793](E:\newbie\cpp_code\images\image-20211105094717793.png)

没有所谓的else if整体实际上是把else{ if{}}写到了一行中，如下两个代码块含义相同：

```c++
int main()
{
	int x = 6;
	if (x)
    {
        std::cout << "HelloWorld" << std::endl;
    }
	else if (x == 5)  //只有当if失败的情况下才会去执行else后面的代码
    {
        std::cout << "Unequal" << std::endl;
    }
	std::cin.get();
}
```

```c++
int main()
{
	int x = 6;
	if (x)
    {
        std::cout << "HelloWorld" << std::endl;
    }
	else
    {
        if (x == 5)
        {
            std::cout << "Unequal" << std::endl;
        }
    }
	std::cin.get();
}
```

作者认为编程可以分为数学编程和逻辑编程两大部分。

## 【Extra】Best VS setup for C++ projects

在VS中创建一个新的空项目，观察创建好的项目文件夹，`.vcxproj`是我们创建的项目文件，本质上是一个xml。

![image-20211105101854686](E:\newbie\cpp_code\images\image-20211105101854686.png)

这几个看起来像文件夹的实际不是文件夹，而是过滤器，比如右键项目进行添加，发现没有添加文件夹，只有添加过滤器。过滤器是以这种虚拟文件夹的形式工作，过滤器视图中文件可以随意放置，与实际的文件夹并无关系，只是一个用来将东西分类的界面。

![image-20211105102250867](E:\newbie\cpp_code\images\image-20211105102250867.png)

在这种视图中源文件过滤器中创建的文件在实际文件夹中会和项目文件放在一起比较混乱。

![image-20211105102721064](E:\newbie\cpp_code\images\image-20211105102721064.png)

如果我们想单独创建一个source的文件夹来存放所有的源代码以区分与项目代码，就需要切换项目视图

![image-20211105102934635](E:\newbie\cpp_code\images\image-20211105102934635.png)

这就能看到真实的项目文件夹了，右键项目添加，就可以新建文件夹

![image-20211105103114052](E:\newbie\cpp_code\images\image-20211105103114052.png)

在Debug模式（默认设置）下生成项目，会把中间文件放在项目目录下的Debug文件中，把实际可运行的ese文件放在和sln文件一起的那个Debug目录下。如此设计有一定非人性，我们需要自行配置：

![image-20211105104546874](E:\newbie\cpp_code\images\image-20211105104546874.png)

如果不了解$符号后这些宏表示什么意思，可以通过下拉三角<编辑>去查看宏，

![image-20211105105041763](E:\newbie\cpp_code\images\image-20211105105041763.png)

## 11. Loops in C++ (for loops, while loops)

### 11.1. for loops

```c++
#include <iostream>
#include "Log.h"

int main()
{
	for (int i = 0; i < 5; i++)
	{
		Log("HelloWorld");
	}
	std::cin.get();
}
```

for (初始条件; 结束条件; 执行的语句)

其中，初始条件在for循环开始前执行一次，执行语句是每次迭代结束后都要执行的语句，结束条件是执行完循环体和执行语句后进行的比较。

```c++
#include <iostream>
#include "Log.h"

int main()
{
	int i = 0;
	bool condition = true;
	for ( ; condition; )
	{
		Log("HelloWorld");
		std::cout << i << std::endl;
		i++;
		if (!(i < 5))
			condition = false;
	}
}
```

上面示例说明了for loop各部分执行的顺序：

1. 初始条件
2. 条件判断
3. 循环体
4. 执行语句

如果条件判断结果为true，则循环执行3、4，否则结束循环

### 11.2. while loops

```c++
#include <iostream>
#include "Log.h"

int main()
{
	int i = 0;
	while (i < 5)
	{
		Log("HelloWorld");
		std::cout << i << std::endl;
		i++;
	}
    std::cin.get();
}
```

### 11.3. 小结

具体选择for loops还是while loops其实主要取决于是否需要新的变量。

如果条件判断已经有一个变量的情况下，通常使用while loops，因为它只需要提供条件，而不用每次循环都改变条件。循环前也不用声明变量，因为条件布尔值已经声明好了，可以直接使用while就好了。不需要使用前声明变量或每次更新值。

而遍历数组时，数组大小确定，推荐使用for loops，因为一样的代码跑十遍的时候，需要10遍中有变量，而且该变量在访问数组的时候有用时

### 11.4. do while loops

```c++
bool condition = false;
do
{
	Log("HelloWorld");
} while (condition);
```

它与while loops的唯一区别就是它的循环体至少会被执行一次。

## 12. Control flow in C++(continue, break, return)

- `continue`：如果还能进行迭代的话直接进行下一次的迭代，否则结束循环。

```c++
#include <iostream>
#include "Log.h"

int main()
{
	for (int i = 0; i < 5; i++)
	{
		if (i > 2)
		{
			continue;
		}
		Log("HelloWorld");
		std::cout << i << std::endl;
	}
	std::cin.get();
}
```

- `break`：直接跳出循环。

```c++
#include <iostream>
#include "Log.h"

int main()
{
	for (int i = 0; i < 5; i++)
	{
		if (i > 2)
		{
			break;;
		}
		Log("HelloWorld");
		std::cout << i << std::endl;
	}
	std::cin.get();
}
```

- `return`：直接完全地退出函数。如果返回类型时void，则只需要return就行；如果函数需要返回值，在输入return时就必须要提供值。return不用像break和continue那样在循环中使用，return可以在代码的任何地方。



## 13. Pointers（raw pointer）

### 13.1. Pointer的本质

**pointer是一个数字，一个整数，它存储一个内存地址。**把内存想象成一条街，一条一维的线型的街，街上有很多房子，每个房子都有地址，每一个带地址的房子都可以想象成一个byte，它是一个字节的数据。我们需要一个方法去给所有字节取址，比如有人从网上买了东西，并且要送货上门，就必须要有房子的地址。

pointer本身是没有类型的，而我们规定的类型最直观的理解可能是它所指向的地址中的数据可能的类型。

```c++
void* ptr = 0;  //赋值为0，是表示这个指针式无效的，也就是它不是一个有效的内存地址。
```

也可以写作

```c++
void* ptr = NULL; 
```

NULL的含义也是#define 0

![image-20211105141923136](E:\newbie\cpp_code\images\image-20211105141923136.png)

或者赋值为c++的一个关键字nullptr

```c++
void* ptr = nullptr;  //这是在c++11中引入的
```

### 13.2. `&`取址符

`&`取址符

```c++
int var = 8;
void* ptr = &var;  //在变量前加上取址符，实际上是在获取它的内存地址，然后把拿到的变量的内存地址把它赋给一个叫ptr的新变量
```

在内存中查看这个地址：

![image-20211105142758150](E:\newbie\cpp_code\images\image-20211105142758150.png)

### 13.3. `*`寻址符

当我们拿到了内存的地址之后该如何去访问地址中的内容呢？

在指针变量前假`*`，如下：

```c++
int var = 8;
void* ptr = &var;  //&+变量名获取变量的内存地址

*ptr  //*+指针获取指针指向内存地址的内容
```

我们可以向指针指向的内存中读取或者写入，如下图所示，给ptr指向的内存中存入10，但是意外的报错了，这是因为我们给定的指针ptr的类型是void，计算机怎么能把一个值写到一个void指针里去呢？

即如果是void指针，计算机不知道这个指针指的内存是几个字节，也就没办法像这个内存中存入那种数据类型。也就是说我们在使用指针时需要告诉指针它指向的是什么类型。

![image-20211105174724132](E:\newbie\cpp_code\images\image-20211105174724132.png)

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main()
{
	int var = 8;
	int* ptr = &var;  //赋值为0，是表示这个指针式无效的，也就是它不是一个有效的内存地址。
	*ptr = 10;
	LOG(var);
	std::cin.get();
}
```

### 13.4.让内存为我们分配特定大小

目前我们创建变量的方法是在内存的stack中创建变量，内存分为stack和heap，两者的区别后面会详细讲到。另一个方法是我们可以在heap中创建变量。

为了让内存为我们分配特定大小就可以使用char*，因为我们清楚char占用一个字节。如下：

```c++
char* buffer = new char[8];
```

上述代码实际做的事是为我们分配了8个字节的内存，并返回一个指向这块内存的开始地址的指针。

然后在使用`memset`函数来用指定的数据去填充一块内存，它接受一个指针，指向内存快的开始处，一个值，比如0，然后是大小即填充几个字节，用法如下：

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main()
{
	char* buffer = new char[8];
	memset(buffer, 0, 8);
    
    delete[] buffer;

	std::cin.get();
}
```

我们使用到了new这个关键字，它指定的数据是分配在heap上的，我们还需要在处理完后删除这个数据。new和delete都是在heap上操作内存，最后还可以用`buffer = nullptr;`来回收指针。

> 要强调的一点是，指针本身也只是变量，这些变量也存储在内存之中。
>
> 如下我们创建一个二级指针，然后来查看内存
>
> ```c++
> #include <iostream>
> 
> #define LOG(x) std::cout << x << std::endl;
> 
> int main()
> {
> 	char* buffer = new char[8];
> 	memset(buffer, 0, 8);
> 
> 	char** ptr = &buffer;  //指针的指针
> 
> 	delete[] buffer;
> 	std::cin.get();
> }
> ```
>
> 下图中二级指针指向的是一级指针所在的地址，可以看到这个地址的存法是高位到低位倒序存储的，重新倒序组合起来就是一级指针实际指向的地址。
>
> ![image-20211105183450479](E:\newbie\cpp_code\images\image-20211105183450479.png)



## 14. Reference

### 14.1 简单的引用

事实上reference只是指针的一个扩展，但是在使用上还是有一些差别，最终引用只是指针的语法糖，是指针更易读。

对于指针，我们可以创建一个新的指针并赋予nullptr，而引用不行，引用变量必须引用一个已经存在的变量，这个变量本身并不是一个新的变量。

```c++
#include <iostream>

int main()
{
	int a = 5;
	//int* ptr = &a;  //ptr存的是a的地址
	int& ref = a;  //ref实际上只是a的一个别名，和指向同一个地址
	std::cin.get();
}
```

在编译过程中，并不会创建两个变量a和引用变量ref，而是只有一个变量啊，但是我们却可以把ref昂做a来用。

这种情况下，引用并不是一个指针，编译器没有必要创建一个新的变量。

### 14.2. 复杂的引用

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

void Increment(int value)
{
	value++;
}

int main()
{
	int a = 5;
	Increment(a);  //这里是传值调用，不是引用或者指针
	LOG(a);

	std::cin.get();
}
```

**传值调用**，调用过程中程序将会拷贝参数值5到这个函数里，直接拷贝将会创造一个全新的变量value。因为上述Increment方法相当于只处理的value变量，而不改变a。

通常我们会获取函数返回的值赋给一个变量，来获取函数处理过的而变量，如果我们想通过上述返回void的函数来影响a的值，就需要使用**引用传递**。

聪明的方法就是我们不传a这个之本身给函数，而是把a的内存地址传给函数，操作如下：

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

void Increment(int* value)
{
	(*value)++;  //*解引用回去对应内存地址中的值
}

int main()
{
	int a = 5;
	Increment(&a);  //&获取a的地址传给函数
	LOG(a);

	std::cin.get();
}
```

注意`*value++;`是给代表内存地址的value增1而不是实际的值。因为操作符的优先级递增符号会优先执行，所以需要给*和value加一个括号`(*value)++`。

其实还有一个更简便的方法，如下：

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

void Increment(int& value)  //把指针改成引用的形式
{
	value++;
}

int main()
{
	int a = 5;
	Increment(a);  //传入的参数依旧是a
	LOG(a);

	std::cin.get();
}
```

相当于传进去的还是a，但是函数获取的并不是复制出来的a的值，而是a的引用--value。

引用能做的指针都能做，指针比起引用更强大一点。

**但是在上述的情况下，建议使用引用，代码会更简洁可读性更高，而且引用会让源码看起来干净很多。**

**注意：**

 -  **一旦声明了一个引用，就不能更改它所引用的对象。**

    ```c++
    #include <iostream>
    
    #define LOG(x) std::cout << x << std::endl;
    
    void Increment(int& value)  //把指针改成引用的形式
    {
    	value++;
    }
    
    int main()
    {
    	int a = 5;
        int b = 8:
        
        int& ref = a;
        ref = b;  //这里的操作并不是让ref引用b，而是直接把b的值赋给ref引用的对象，也就是a，那么a也会等于8
        
    	Increment(a);
    	LOG(a);
    
    	std::cin.get();
    }
    ```

- 当声明一个引用时，必须将一个实际的变量赋值给它。

  ```c++
  int& ref;  //这种写法是不允许的
  ```

### 如果我们确实想改变ref所代指的对象该怎么办呢？

我们需要创建一些变量使它先指向a，然后再让它指向b。仔细分析一下这句话，使用指针就可以实现这个目的。***<u>？？？？？？？？？？？？？？？？？？？？？？？？</u>***

```c++
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main()
{
	int a = 5;
    int b = 8:
    
    int* ref = &a;
    *ref = 2;
    ref = &b;
    *ref = 0;
    
    LOG(a);
	LOG(b);

	std::cin.get();
}
```
