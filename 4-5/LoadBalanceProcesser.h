#pragma once

class URLProcesser;
class LoadBalanceProcesser : public URLProcesser
{
public:
	LoadBalanceProcesser(shared_ptr<HttpClient> httpClient);
	~LoadBalanceProcesser();

	virtual void Send(vector<string>& urls) override;

};
