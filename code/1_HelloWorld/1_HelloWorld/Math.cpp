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
#define INTEGER int  //����ǰ���ú����滻�����üӷֺ�

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
#include "EndBrace.h"  //��һ�����Ǽ򵥴ֱ��Ĵ�EndBrace.h��Ȼ������������ճ���ڵ�ǰ�ļ��У������ܳ������header�ļ���������ô�õ��ˡ�
*/
