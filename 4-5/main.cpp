#include "stdafx.h"

void LoadConfig(string filename, map<string, vector<string>>& config)
{
	ifstream f(filename);
	if (f.fail()) {
		cout << "Load " << filename << " failed\n";
	}

	string line;
	while (!f.eof()) {
		getline(f, line);

		istringstream ss(line);
		string token;
		vector<string> tokens;
		while (getline(ss, token, ':')) {
			tokens.emplace_back(token);
		}

		if (tokens.size() != 2) {
			cout << "Config format err\n";
			continue;
		}

		string host = tokens[0];
		
		tokens.clear();
		ss.clear();
		ss.str(tokens[1]);
		while (getline(ss, token, ',')) {
			tokens.emplace_back(token);
		}

		for (auto& ip : tokens) {
			config[host].emplace_back(ip);
		}
	}
}

void LoadBlackList(string filename, set<string>& list)
{
	ifstream f(filename);

	if (f.fail()) {
		cout << "Load BlackList " << filename << " failed\n";
		return;
	}
	
	string line;
	string token;
	while (!f.eof()) {
		getline(f, line);
		istringstream ss(line);
		while (getline(ss, token, ',')) {
			list.emplace(token);
		}
	}
}

int main()
{
	map<string, vector<string>> config;
	LoadConfig("config", config);

	set<string> blackList;
	LoadBlackList("blacklist", blackList);
	
	
	return 0;
}