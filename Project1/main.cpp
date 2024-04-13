#include "stdafx.h"
#include "RelationshipAnalyzer.h"

string ReadFile(string filename) {
	fstream file(filename);
	if (file.fail()) {
		return "";
	}

	string script((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	//123
	return script;
}

int main()
{
	string script = ReadFile("test.txt");
	return 0;
}