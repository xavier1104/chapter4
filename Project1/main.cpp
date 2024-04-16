#include "stdafx.h"
#include "RelationshipAnalyzer.h"
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

	shared_ptr<RelationshipAnalyzer> rsa = make_shared<RelationshipAnalyzerAdapter>();

	rsa->Parse(script);

	string name1 = "A", name2 = "B";
	set<string> friends;
	while (1) {
		cout << "Please enter two names : ";
		cin >> name1 >> name2;

		if (name1 == name2) {
			break;
		}

		friends = rsa->GetMutualFriends(name1, name2);

		cout << name1 << " and " << name2 << " common friends are : ";
		for (const string& f : friends) {
			cout << f << ' ';
		}
		cout << '\n';
	}

	return 0;
}