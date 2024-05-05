#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"
#include "BlackListProcesser.h"
#include "LoadBalanceProcesser.h"
#include "ServiceDiscoverProcesser.h"
#include "BlackListException.h"
#include "RequestFailException.h"
#include "FakeHttpClient.h"

int main()
{
	vector<string> urls = { "http://waterballsa.tw/mail" };
	shared_ptr<HttpClient> httpClient = 
		make_shared<BlackListProcesser>(make_shared<LoadBalanceProcesser>(make_shared<ServiceDiscoverProcesser>(make_shared<FakeHttpClient>())));
	
	while (1) {
		cout << "Press Enter to send url\n";
		cin.get();

		try {
			httpClient->Send(urls);
		}
		catch (const BlackListException& e) {
			cerr << e.what();
			cin.get();
			exit(0);
		}
	}
	return 0;
}