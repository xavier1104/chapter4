#pragma once

class RelationshipGraph;
class RelationshipAnalyzer
{
public:
	RelationshipAnalyzer();
	~RelationshipAnalyzer();

	virtual shared_ptr<RelationshipGraph> Parse(string script) = 0;
};