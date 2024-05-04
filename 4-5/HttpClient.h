#pragma once

class HttpClient
{
public:
	HttpClient();
	~HttpClient();

	virtual void Send(vector<string>& urls) = 0;
};