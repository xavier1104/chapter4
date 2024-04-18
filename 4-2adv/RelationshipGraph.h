#pragma once

class RelationshipGraph
{
public:
	RelationshipGraph();
	~RelationshipGraph();

	bool HasConnection(string name1, string name2);
};