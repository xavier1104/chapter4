#include "stdafx.h"
#include "RelationshipGraph.h"
#include "BGLRelationshipGraph.h"
#include "RelationshipAnalyzerAdapter.h"

RelationshipAnalyzerAdapter::RelationshipAnalyzerAdapter()
{

}

RelationshipAnalyzerAdapter::~RelationshipAnalyzerAdapter()
{

}

shared_ptr<RelationshipGraph> RelationshipAnalyzerAdapter::Parse(string script)
{
	istringstream iss(script);

	string line;
	string target;
	string friendName;
	map<string, set<string>> relationship;
	while (getline(iss, line)) {
		target = line.at(0);
		relationship[target] = {};
		auto& friends = relationship[target];

		int i = 3;
		while (i < line.size()) {
			friendName = line.at(i);
			friends.emplace(friendName);
			i += 2;
		}
	}

	return make_shared<BGLRelationshipGraph>(relationship);
}