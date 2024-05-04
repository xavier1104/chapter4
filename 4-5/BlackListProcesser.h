#pragma once

class URLProcesser;
class BlackListProcesser : public URLProcesser
{
public:
	BlackListProcesser(shared_ptr<HttpClient> httpClient, set<string>& list);
	~BlackListProcesser();

	void Send(vector<string>& urls) override;

private:
	set<string> list_;
};