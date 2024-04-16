#include "stdafx.h"
#include "SuperRelationshipAnalyzer.h"

SuperRelationshipAnalyzer::SuperRelationshipAnalyzer()
{
}

SuperRelationshipAnalyzer::~SuperRelationshipAnalyzer()
{
}

void SuperRelationshipAnalyzer::Parse(string script)
{
	istringstream iss(script);
	
	string line;
	string target;
	string f;
	while (getline(iss, line)) {
		target = line.at(0);
		int i = 5;
		if (i >= line.size()) {
			continue;
		}

		f = line.at(i);
		friendLists[target].emplace(f);
	}
}

bool SuperRelationshipAnalyzer::IsMutualFriend(string targetName, string name1, string name2)
{
	auto&& it1 = friendLists.find(name1);
	auto&& it2 = friendLists.find(name2);

	if (it1 == friendLists.end() || it2 == friendLists.end()) {
		return false;
	}

	return (it1->second.find(targetName) != it1->second.end()) && (it2->second.find(targetName) != it2->second.end());
}
