#include "stdafx.h"
#include "RelationshipGraph.h"
#include "RelationshipAnalyzerAdapter.h"

string ReadFile(string filename) {
	fstream file(filename);
	if (file.fail()) {
		return "";
	}

	string script((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

	return script;
}

int main()
{
	string script = ReadFile("test.txt");

	shared_ptr<RelationshipAnalyzer> analyzer = make_shared<RelationshipAnalyzerAdapter>();
	shared_ptr<RelationshipGraph> graph = analyzer->Parse(script);

	cout << graph->HasConnection("A", "B");
	return 0;
}