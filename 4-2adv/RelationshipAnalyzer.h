#pragma once

class RelationshipAnalyzer
{
public:
	RelationshipAnalyzer();
	~RelationshipAnalyzer();

	void Parse(string script) = 0;
};