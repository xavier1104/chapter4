#pragma once

#include "RelationshipGraph.h"

class RelationshipGraph;
class BGLRelationshipGraph : public RelationshipGraph
{
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

public:
	BGLRelationshipGraph(map<string, set<string>>& relationship);
	~BGLRelationshipGraph();

	virtual bool HasConnection(string name1, string name2) override;

private:
	map<string, int> code_;
	vector<int> component_;
	Graph graph_;
};