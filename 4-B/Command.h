#pragma once

class Member;
class Command
{
public:
	Command(int quota, string name);
	~Command();

	int GetQuota() { return quota_; }
	string GetName() { return name_; }
	virtual bool CheckPermission(shared_ptr<Member> member) { return true; }
	virtual void Execute() {}

private:
	int quota_;
	string name_;
};