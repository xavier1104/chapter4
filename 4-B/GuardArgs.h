#pragma once

#include "DataType.h"

struct SGuard
{
	virtual ~SGuard() = default;
};

struct SCommandGuard : public SGuard
{
	SCommandGuard(eCommand cmd) {
		cmd_ = cmd;
	}
	
	eCommand cmd_;
};

struct SMemberLargerOrEqual10Guard : public SGuard
{
	
};

struct SMemberLessThan10Guard : public SGuard
{

};

struct STimeElapsedGuard : public SGuard
{
	STimeElapsedGuard(int seconds) {
		seconds_ = seconds;
	}

	int seconds_;
};