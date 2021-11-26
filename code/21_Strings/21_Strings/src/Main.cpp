#include <iostream>
#include <string>
#include <stdlib.h>

void PrintString(const std::string& string)
{
	std::cout << string << std::endl;
}


int main()
{
	const char* name = "Melissa";  //使用const标识符是想使得name是不可修改的，
	std::cout << name << std::endl;
	char name2[8] = { 'M', 'e', 'l', 'i', 's', 's', 'a', '\0'};
	std::cout << name2 << std::endl;
	std::string name3 = "Melissa";
	std::cout << name3 << std::endl;
	name3 += "go";
	std::cout << name3 << std::endl;
	std::string name4 = std::string("Melissa") + "go";
	std::cout << name4 << std::endl;

	bool contains = name3.find("sa") != std::string::npos;

	PrintString(name4);
	PrintString("");
	//////////////////////////////////////////////
	const char name5[8] = "Melissa";
	const char name6[10] = "Meli\0ssa";
	std::cout << strlen(name5) << std::endl;
	std::cout << strlen(name6) << std::endl;

	const char* name7 = "Melissa";
	char name8[] = "Melissa";
	std::cout << name8 << std::endl;
	name8[2] = '0';
	std::cout << name8 << std::endl;
	name8[3] = '0';
	std::cout << name8 << std::endl;

	/////////////////////////////////////////////
	const wchar_t* name9 = L"Melissa";
	const char16_t* name10 = u"Melissa";
	const char32_t* name11 = U"Melissa";
	const char* name12 = u8"Melissa";

	/////////////////////////////////////////////
	using namespace std::string_literals;

	std::string  name13 = "melissa"s + "go";
	std::string  name14 = R"(melissa
		go
		wo)";
	std::cout << name14 << std::endl;
	std::string  name15 = "melissa"
		"go"
		"wo";
	std::cout << name15 << std::endl;
	std::string  name16 = "melissa\n"
		"go\n"
		"wo\n";
	std::cout << name16 << std::endl;

	std::cin.get();
}