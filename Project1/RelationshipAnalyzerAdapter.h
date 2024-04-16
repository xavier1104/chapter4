#pragma once

#include "RelationshipAnalyzer.h"

class SuperRelationshipAnalyzer;
class RelationshipAnalyzerAdapter : public RelationshipAnalyzer
{
public:
	RelationshipAnalyzerAdapter();
	~RelationshipAnalyzerAdapter();

	void Parse(string script) override;
	set<string> GetMutualFriends(string name1, string name2) override;

private:
	shared_ptr<SuperRelationshipAnalyzer> analyzer_;
	set<string> candidates_;
};