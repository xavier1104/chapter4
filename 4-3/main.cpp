#include "stdafx.h"
#include "Database.h"
#include "VirtualDatabaseProxy.h"
#include "PasswordProtectedDatabaseProxy.h"
#include "Employee.h"

void PrintEmployee(shared_ptr<Employee> employee, shared_ptr<Database> db) {
	if (!employee || !db) {
		return;
	}

	cout << "id : " << employee->id_ << '\n';
	cout << "name : " << employee->name_ << '\n';
	cout << "age : " << employee->age_ << '\n';
}

int main()
{
	shared_ptr<Database> db = make_shared<PasswordProtectedDatabaseProxy>();
	int id = 0;
	while (1) {
		cout << "Enter employee id : ";
		cin >> id;

		shared_ptr<Employee> employee = db->GetEmployeeById(id);

		if (!employee) {
			cout << "Employee not exist\n";
		}
		else {
			PrintEmployee(employee, db);
			if (employee->subordinateIds_.size()) {
				cout << "subordinates : \n";
				for (auto& subId : employee->subordinateIds_) {
					auto sub = db->GetEmployeeById(subId);
					PrintEmployee(sub, db);
				}
			}
		}
	}

	cout << "press key to continue \n";
	cin.get();
	return 0;
}