#include "stdafx.h"
#include "Employee.h"
#include "RealDatabase.h"

RealDatabase::RealDatabase()
{
}

RealDatabase::~RealDatabase()
{
}

shared_ptr<Employee> RealDatabase::GetEmployeeById(int id)
{
	auto&& it = employees_.find(id);
	if (it == employees_.end()) {
		return nullptr;
	}
	return it->second;
}

void RealDatabase::AddEmployee(shared_ptr<Employee> employee)
{
	if (employee) {
		employees_[employee->id_] = employee;
	}
}
