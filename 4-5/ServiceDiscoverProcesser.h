#pragma once

class URLProcesser;
class HttpClient;
class ServiceDiscoverProcesser : public URLProcesser
{
public:
	ServiceDiscoverProcesser(shared_ptr<HttpClient> httpClient);
	~ServiceDiscoverProcesser();

	virtual void Send(vector<string>& urls) override;
	void AddInvalid(string url);

private:
	vector<string> ReplacedUrls(string& url);
	void LoadConfig(string filename);

private:
	map<string, vector<string>> config_;
	list<string> inValidIPs_;
};