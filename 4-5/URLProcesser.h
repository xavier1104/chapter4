#pragma once

class HttpClient;
class URLProcesser : public HttpClient
{
public:
	URLProcesser(shared_ptr<HttpClient> httpClient);
	~URLProcesser();

	virtual void Send(vector<string>& urls) {};

protected:
	shared_ptr<HttpClient> httpClient_;
};