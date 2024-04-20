#pragma once

#include "stdafx.h"
#include "Employee.h"

class Database
{
public:
	virtual shared_ptr<Employee> GetEmployeeById(int id) = 0;
};