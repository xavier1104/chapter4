#pragma once

#include "VirtualDatabaseProxy.h"

class PasswordProtectedDatabaseProxy : public VirtualDatabaseProxy
{
public:
	PasswordProtectedDatabaseProxy();
	~PasswordProtectedDatabaseProxy();

	virtual shared_ptr<Employee> GetEmployeeById(int id) override;
};