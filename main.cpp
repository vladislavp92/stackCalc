#include <iostream>
#include "Calc.h"
#include "Pow.h"


int main()
{
	setlocale(LC_ALL, "Russian");
	//std::cout << "¬ведите выражение:" << std::endl;

	Calculator c;
	c.SupportOperation('^', new Pow);
	//c.SupportOperation('%', ModDiv);
	c.IsSupported('^');
	std::string question;
	std::cin >> question;
	double reply = c.Calculate(question);
	std::cout << reply << std::endl;
}