#pragma once

#include "Employee.h"

class RealEmployee : public Employee
{
public:
	RealEmployee(int id, string name, int age, set<int>& subordinateIds);
	~RealEmployee();
};