#pragma once

#include "Database.h"

class RealDatabase;
class VirtualDatabaseProxy : public Database
{
public:
	VirtualDatabaseProxy();
	~VirtualDatabaseProxy();

	virtual shared_ptr<Employee> GetEmployeeById(int id) override;

private:
	shared_ptr<Employee> LoadEmployeeFromFile(int id);
	shared_ptr<Employee> ParseEmployee(string& line);
private:
	shared_ptr<RealDatabase> db_;
};