#pragma once

class URLProcesser;
class HttpClient;
class ServiceDiscoverProcesser : public URLProcesser
{
public:
	ServiceDiscoverProcesser(shared_ptr<HttpClient> httpClient, map<string, vector<string>>& config);
	~ServiceDiscoverProcesser();

	virtual void Send(vector<string>& urls) override;
	void AddInValidIP(string& ip);

private:
	vector<string> ReplacedUrls(string& url);

private:
	map<string, vector<string>> config_;
	set<string> inValidIPs_;
};