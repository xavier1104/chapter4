#include "stdafx.h"
#include "RequestFailException.h"
#include "FakeHttpClient.h"

FakeHttpClient::FakeHttpClient()
{
}

FakeHttpClient::~FakeHttpClient()
{
}

void FakeHttpClient::Send(vector<string>& urls)
{
	if (urls.size() == 0) {
		return;
	}

	if (rand() % 2 == 0) {
		cout << "[SUCCESS] " << urls[0] << '\n';
	}
	else {
		cerr << "[FAIL] " << urls[0] << '\n';
		throw RequestFailException(urls[0]);
	}
}
