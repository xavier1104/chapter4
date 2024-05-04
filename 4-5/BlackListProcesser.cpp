#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"
#include "BlackListProcesser.h"

BlackListProcesser::BlackListProcesser(shared_ptr<HttpClient> httpClient, set<string>& list)
	:URLProcesser(httpClient)
	,list_(list)
{
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
			
			cout << "host in black list!\n";
			cin.get();
			exit(0);
		}
	}

	httpClient_->Send(urls);
}
