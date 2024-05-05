#pragma once

#include "HttpClient.h"

class HttpClient;
class FakeHttpClient : public HttpClient
{
public:
	FakeHttpClient();
	~FakeHttpClient();

	void Send(vector<string>& urls) override;
};