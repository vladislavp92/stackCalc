#include <iostream>
#include "Calc.h"


int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "������� ���������:" << std::endl;
	std::string question;
	std::cin >> question;
	Calculator c;
	double reply = c.Calculate(question);
	std::cout << reply << std::endl;
}