#pragma once

#include "RelationshipAnalyzer.h"

class RelationshipAnalyzerAdapter : public RelationshipAnalyzer
{
public:
	RelationshipAnalyzerAdapter();
	~RelationshipAnalyzerAdapter();

	virtual shared_ptr<RelationshipGraph> Parse(string script) override;
};