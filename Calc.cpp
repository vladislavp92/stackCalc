#include "Calc.h"
#include <iostream>
#include <stack>
#include <string>

enum class CharGroup { digit, operation, bracket };
enum class Priority { min, low, high, max };

Priority FindOutOperationPriority(char c)
{
	switch (c)
	{
	case '+':
		return Priority::low;
		break;
	case '-':
		return Priority::low;
		break;
	case '*':
		return Priority::high;
		break;
	case '/':
		return Priority::high;
		break;
	}
}
CharGroup FindOutCharGroup(char c)
{
	CharGroup group;
	if (c <= '9' && c >= '0')
	{
		group = CharGroup::digit;
	}
	else if (c == '(' || c == ')')
	{
		group = CharGroup::bracket;
	}
	else
	{
		group = CharGroup::operation;
	}

	return group;
}
void DoCalculation(std::stack<double>& operands, std::stack<char>& operations)
{
	double RightOperand = operands.top();
	operands.pop();
	char Operation = operations.top();
	operations.pop();
	double LeftOperand = operands.top();
	operands.pop();
	double Result;

	switch (Operation)
	{
	case '+':
		Result = LeftOperand + RightOperand;
		break;
	case '-':
		Result = LeftOperand - RightOperand;
		break;
	case '*':
		Result = LeftOperand * RightOperand;
		break;
	case '/':
		Result = LeftOperand / RightOperand;
		break;
	}
	operands.push(Result);
}
void HandleDigit(char c, std::stack<double>& operands, std::stack<char>& operations)
{
	operands.push(c-'0');
}
void HandleOperation(char c, std::stack<double>& operands, std::stack<char>& operations)
{
	if (operations.empty())
	{
		operations.push(c);
	}
	else
		if (FindOutCharGroup(operations.top()) == CharGroup::bracket)
		{
			operations.push(c);
		}
		else
		{
			Priority c_priority = FindOutOperationPriority(c);
			Priority top_c_priority = FindOutOperationPriority(operations.top());
			if (c_priority > top_c_priority)
			{
				operations.push(c);
			}
			else
			{
				DoCalculation(operands, operations);
				operations.push(c);
			}
		}
}
void HandleBracket(char c, std::stack<double>& operands, std::stack<char>& operations)
{
	if (c == '(')
	{
		operations.push(c);
	}
	else if (c == ')')
	{
		while (operations.top() != '(')
		{
			DoCalculation(operands, operations);
		}
		operations.pop();
	}
}

double Calculator::Calculate(std::string expression)
{
	std::stack<double> operands;
	std::stack<char> operations;

	for (int i = 0; i != expression.size(); i++)
	{
		CharGroup group = FindOutCharGroup(expression[i]);
		switch (group)
		{
		case CharGroup::digit:
			HandleDigit(expression[i], operands, operations);
			break;
		case CharGroup::bracket:
			HandleBracket(expression[i], operands, operations);
			break;
		case CharGroup::operation:
			HandleOperation(expression[i], operands, operations);
			break;
		}
 		//std::cout << expression[i] << " " << group << /n;
	}

	while (!operations.empty())
	{
		DoCalculation(operands, operations);
	}

	return operands.top();
}
