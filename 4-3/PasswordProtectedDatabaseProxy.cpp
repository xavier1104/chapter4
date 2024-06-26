#include "PasswordProtectedDatabaseProxy.h"

PasswordProtectedDatabaseProxy::PasswordProtectedDatabaseProxy()
{
}

PasswordProtectedDatabaseProxy::~PasswordProtectedDatabaseProxy()
{
}

shared_ptr<Employee> PasswordProtectedDatabaseProxy::GetEmployeeById(int id)
{
	shared_ptr<Employee> employee = nullptr;
	char* varValue = nullptr;
	size_t size = 0;
	const char* varName = "PASSWORD";

	errno_t err = _dupenv_s(&varValue, &size, varName);
	if (err) {
		cout << "Error code : " << err;
		cin.get();
		exit(0);
	}

	if (varValue == nullptr) {
		cout << "Environment variable " << varName << " is not set.\n";
		cin.get();
		exit(0);
	}
	else {
		if (strcmp(varValue, "1qaz2wsx") != 0) {
			cout << "Password error!!\n";
			cin.get();
			exit(0);
		}
		else {
			employee = VirtualDatabaseProxy::GetEmployeeById(id);
		}
	}
	
	return employee;
}
