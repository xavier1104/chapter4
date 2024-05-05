#pragma once

class URLProcesser;
class BlackListProcesser : public URLProcesser
{
public:
	BlackListProcesser(shared_ptr<HttpClient> httpClient);
	~BlackListProcesser();

	void Send(vector<string>& urls) override;
	
private:
	void LoadList(string filename);

private:
	set<string> list_;
};