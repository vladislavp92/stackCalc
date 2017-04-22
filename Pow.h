#pragma once
#include <math.h>

#include "BinOperator.h"

class Pow : public BinOperator
{
public:
	virtual double Execute(double left, double right) const
	{
		return pow(left, right);
	}
	virtual Priority GetPriority() const
	{
		return Priority::max;
	}
};