#pragma once

class Employee
{
public:
	Employee(int id, string name, int age, set<int>& subordinateIds);
	~Employee();

public:
	int id_;
	string name_;
	int age_;
	set<int> subordinateIds_;
};