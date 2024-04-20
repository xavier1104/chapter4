#include "stdafx.h"
#include "Employee.h"
#include "RealEmployee.h"
#include "RealDatabase.h"
#include "VirtualDatabaseProxy.h"

VirtualDatabaseProxy::VirtualDatabaseProxy()
{
	db_ = make_shared<RealDatabase>();
}

VirtualDatabaseProxy::~VirtualDatabaseProxy()
{
}

shared_ptr<Employee> VirtualDatabaseProxy::GetEmployeeById(int id)
{
	shared_ptr<Employee> employee = db_->GetEmployeeById(id);
	if (!employee) {
		employee = LoadEmployeeFromFile(id);
		db_->AddEmployee(employee);
	}

	return employee;
}

shared_ptr<Employee> VirtualDatabaseProxy::LoadEmployeeFromFile(int id)
{
	fstream f("data.txt");
	if (f.fail()) {
		return nullptr;
	}

	int targetLine = id + 1;
	string line = "";
	for (int i = 0; i < targetLine; ++i) {
		if (!getline(f, line)) {
			return nullptr;
		}
	}

	return ParseEmployee(line);
}

shared_ptr<Employee> VirtualDatabaseProxy::ParseEmployee(string& line)
{
	vector<string> attrs;
	boost::split(attrs, line, boost::is_any_of(" "));
	int id = stoi(attrs[0]);
	string name = attrs[1];
	int age = stoi(attrs[2]);
	set<int> subordinateIds = {};
	if (attrs.size() > 3) {
		string subordinatesStr = attrs[3];
		vector<string> subs;
		boost::split(subs, subordinatesStr, boost::is_any_of(","));
		for (string& sub : subs) {
			subordinateIds.emplace(stoi(sub));
		}
	}

	shared_ptr<Employee> employee = make_shared<RealEmployee>(id, name, age, subordinateIds);
	return employee;
}