#include "stdafx.h"
#include "BGLRelationshipGraph.h"

BGLRelationshipGraph::BGLRelationshipGraph(map<string, set<string>>& relationship)
{
	int i = 0;
	for (auto&& [target, friends] : relationship) {
		code_[target] = i;
		boost::add_vertex(graph_);
		i++;
	}

	for (auto&& [target, friends] : relationship) {
		for (auto&& f : friends) {
			boost::add_edge(code_[target], code_[f], graph_);
		}
	}

	component_.resize(boost::num_vertices(graph_));
	boost::connected_components(graph_, &component_[0]);
}

BGLRelationshipGraph::~BGLRelationshipGraph()
{
}

bool BGLRelationshipGraph::HasConnection(string name1, string name2)
{
	int n1 = code_[name1];
	int n2 = code_[name2];

	return component_[n1] == component_[n2];
}
