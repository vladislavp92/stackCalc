#pragma once

enum class Priority { min, low, high, max };

class BinOperator
{
public:
	virtual double Execute(double left, double right) const = 0;
	virtual Priority GetPriority() const = 0;
};