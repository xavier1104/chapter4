#pragma once

class SuperRelationshipAnalyzer
{
public:
	SuperRelationshipAnalyzer();
	~SuperRelationshipAnalyzer();

	void Parse(string script);
	bool IsMutualFriend(string targetName, string name1, string name2);

private:
	map < string, set<string>> friendLists;
};