#include "Calc.h"
#include <iostream>
#include <stack>
#include <string>
#include "BinOperator.h"
#include "Div.h"
#include "Mult.h"
#include "Sub.h"
#include "Summ.h"

Priority Calculator::FindOutOperationPriority(char c)
{
	return SupportedOperations_[c]->GetPriority();
}
CharGroup Calculator::FindOutCharGroup(char c)
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

void Calculator::DoCalculation(std::stack<double>& operands, std::stack<char>& operations)
{
	double RightOperand = operands.top();
	operands.pop();
	char Operation = operations.top();
	operations.pop();
	double LeftOperand = operands.top();
	operands.pop();
	double Result;

	Result = SupportedOperations_[Operation]->Execute(LeftOperand, RightOperand);
	operands.push(Result);
}

Calculator::Calculator()
{
	SupportedOperations_.insert(std::make_pair('+', new Summ));
	SupportedOperations_['-'] = new Sub;
	SupportedOperations_.emplace('*', new Mult);
	SupportedOperations_.insert(std::pair<char, BinOperator*>('/', new Div));
}

void Calculator::HandleDigit(char c, std::stack<double>& operands, std::stack<char>& operations)
{
	operands.push(c-'0');
}
void Calculator::HandleOperation(char c, std::stack<double>& operands, std::stack<char>& operations)
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

void Calculator::HandleBracket(char c, std::stack<double>& operands, std::stack<char>& operations)
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
 }

	while (!operations.empty())
	{
		DoCalculation(operands, operations);
	}
	return operands.top();
}
void Calculator::SupportOperation(char c, BinOperator* op)
{
	SupportedOperations_.emplace(c, op);
}
void Calculator::UnsupportOperation(char c)
{
	SupportedOperations_.erase(c);
}
bool Calculator::IsSupported(char c)
{
	if (SupportedOperations_.find(c) == SupportedOperations_.end())
	{
		return 1;
	}
}
