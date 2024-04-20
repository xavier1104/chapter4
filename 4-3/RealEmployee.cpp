#include "stdafx.h"
#include "RealEmployee.h"

RealEmployee::RealEmployee(int id, string name, int age, set<int>& subordinateIds)
	:Employee(id, name, age, subordinateIds)
{
}

RealEmployee::~RealEmployee()
{
}
