#include <string>
#include <stack>
#include <map>
#include "BinOperator.h"

enum class CharGroup { digit, operation, bracket };
class Calculator
{
public:
	Calculator();
	double Calculate(std::string expression);
	void SupportOperation(char, BinOperator*);
	void UnsupportOperation(char);
	bool IsSupported(char);
private:
	Priority FindOutOperationPriority(char c);
	CharGroup FindOutCharGroup(char c);
	void DoCalculation(std::stack<double>& operands, std::stack<char>& operations);
	void HandleDigit(char c, std::stack<double>& operands, std::stack<char>& operations);
	void HandleOperation(char c, std::stack<double>& operands, std::stack<char>& operations);
	void HandleBracket(char c, std::stack<double>& operands, std::stack<char>& operations);
	std::map <char, BinOperator*> SupportedOperations_;
};
	