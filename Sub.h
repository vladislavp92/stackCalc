#pragma once

#include "BinOperator.h"

class Sub : public BinOperator
{
public:
	virtual double Execute(double left, double right) const
	{
		return left - right;
	}
	virtual Priority GetPriority() const
	{
		return Priority::low;
	}
};