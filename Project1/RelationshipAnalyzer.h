#pragma once

class RelationshipAnalyzer
{
public:
	RelationshipAnalyzer();
	~RelationshipAnalyzer();

	virtual void Parse(string script) = 0;
	virtual void GetMutualFriends(string name1, string name2) = 0;
};