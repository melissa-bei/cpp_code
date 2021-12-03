const char* Log(const char* message)
{
	return message;
}

int Multiply(int a, int b)
{
	Log("Multiply");
	return a * b;
}


/*//6
int Multiply()
{
	return 5 * 2;
}
*/


/*//5
int Multiply(int a, int b)
{
	return a * b;
}
*/


/*//4
int Multiply(int a, int b)
{
	int result = a * b;
	return result;
}
*/


/*//3
#if 0
int Multiply(int a, int b)
{
	int result = a + b;
	return result;
}
#endif
*/


/*//2
#define INTEGER int  //查找前者用后者替换，不用加分号

INTEGER Multiply(int a, int b)
{
	INTEGER result = a + b;
	return result;
}
*/


/*//1
int Multiply(int a, int b)
{
	int result = a + b;
	return result;
#include "EndBrace.h"  //这一步就是简单粗暴的打开EndBrace.h，然后把里面的内容粘贴在当前文件中，即就能彻底理解header文件到底是怎么用的了。
*/
