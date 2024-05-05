#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"
#include "BlackListException.h"
#include "BlackListProcesser.h"

BlackListProcesser::BlackListProcesser(shared_ptr<HttpClient> httpClient)
	:URLProcesser(httpClient)
{
	LoadList("blacklist.txt");
}

BlackListProcesser::~BlackListProcesser()
{
}

void BlackListProcesser::Send(vector<string>& urls)
{
	for (string& url : urls) {
		for (const string& host : list_) {
			size_t pos = url.find(host);
			if (pos == string::npos) {
				continue;
			}
			
			throw BlackListException(host);
		}
	}

	httpClient_->Send(urls);
}

void BlackListProcesser::LoadList(string filename)
{
	list_.clear();

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
			list_.emplace(token);
		}
	}
}
