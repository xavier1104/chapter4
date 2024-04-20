#pragma once

#include "Database.h"

class RealDatabase : public Database
{
public:
	RealDatabase();
	~RealDatabase();

	virtual shared_ptr<Employee> GetEmployeeById(int id) override;
	void AddEmployee(shared_ptr<Employee> employee);

private:
	map<int, shared_ptr<Employee>> employees_;
};