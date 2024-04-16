#include "stdafx.h"
#include "SuperRelationshipAnalyzer.h"
#include "RelationshipAnalyzerAdapter.h"

RelationshipAnalyzerAdapter::RelationshipAnalyzerAdapter()
	:analyzer_(make_shared<SuperRelationshipAnalyzer>())
{
}

RelationshipAnalyzerAdapter::~RelationshipAnalyzerAdapter()
{
}

void RelationshipAnalyzerAdapter::Parse(string script)
{
	istringstream iss(script);
	
	string transformedScript;

	string line;
	string target;
	while (getline(iss, line)) {
		target = line.at(0);
		candidates_.emplace(target);

		int i = 3;
		while (i < line.size()) {
			char friendName = line.at(i);
			transformedScript += (target + " -- " + friendName + '\n');
			i += 2;
		}
	}

	analyzer_->Parse(transformedScript);
}

set<string> RelationshipAnalyzerAdapter::GetMutualFriends(string name1, string name2)
{
	set<string> friends;
	for (string f : candidates_) {
		if (analyzer_->IsMutualFriend(f, name1, name2)) {
			friends.emplace(f);
		}
	}
	return friends;
}
