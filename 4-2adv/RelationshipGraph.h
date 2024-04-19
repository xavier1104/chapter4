#pragma once

class RelationshipGraph
{
public:
	RelationshipGraph();
	~RelationshipGraph();

	virtual bool HasConnection(string name1, string name2) = 0;
};