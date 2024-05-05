#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"
#include "LoadBalanceProcesser.h"

LoadBalanceProcesser::LoadBalanceProcesser(shared_ptr<HttpClient> httpClient)
	:URLProcesser(httpClient)
{
}

LoadBalanceProcesser::~LoadBalanceProcesser()
{
}

void LoadBalanceProcesser::Send(vector<string>& urls)
{
	static int i = 0;
	i = i % urls.size();
	vector<string> selectedURLs = { urls[i] };

	httpClient_->Send(selectedURLs);
	i++;
}
