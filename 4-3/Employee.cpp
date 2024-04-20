#include "stdafx.h"
#include "Employee.h"

Employee::Employee(int id, string name, int age, set<int>& subordinateIds)
	:id_(id)
	,name_(name)
	,age_(age)
	,subordinateIds_(subordinateIds)
{
}

Employee::~Employee()
{
}
