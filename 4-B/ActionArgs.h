#pragma once

#include "DataType.h"

struct SAction
{
	virtual ~SAction() = default;
};

struct SCommandAction : public SAction
{
	SCommandAction(eCommand cmd) {
		cmd_ = cmd;
	}

	eCommand cmd_;
};