#pragma once
#include "BinOperator.h"

class ModDiv : public BinOperator
{
public:
	virtual double Execute(double left, double right) const
	{
		return left % right;
	}
	virtual Priority GetPriority() const
	{
		return Priority::high;
	}
};