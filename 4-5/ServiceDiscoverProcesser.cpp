#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"
#include "ServiceDiscoverProcesser.h"

ServiceDiscoverProcesser::ServiceDiscoverProcesser(shared_ptr<HttpClient> httpClient, map<string, vector<string>>& config)
	:URLProcesser(httpClient)
{
}

ServiceDiscoverProcesser::~ServiceDiscoverProcesser()
{
}

void ServiceDiscoverProcesser::Send(vector<string>& urls)
{
	vector<string> discoveredUrls;
	for (string& url : urls) {
		vector<string> replacedUrls = ReplacedUrls(url);
		for (string& repacedUrl : replacedUrls) {
			replacedUrls.emplace_back(repacedUrl);
		}

		if (replacedUrls.size() == 0) {
			discoveredUrls.emplace_back(url);
		}
	}

	httpClient_->Send(discoveredUrls);
}

vector<string> ServiceDiscoverProcesser::ReplacedUrls(string& url)
{
	vector<string> replacedUrls;
	for (auto&& [host, ips] : config_) {
		size_t pos = url.find(host);
		if (pos == string::npos) {
			continue;
		}

		for (auto& ip : ips) {
			auto&& it = inValidIPs_.find(ip);
			if (it != inValidIPs_.end()) {
				continue;
			}

			string replacedUrl = url;
			replacedUrl.replace(pos, host.length(), ip);
			replacedUrls.emplace_back(replacedUrl);
		}

		break;
	}

	return replacedUrls;
}

void ServiceDiscoverProcesser::AddInValidIP(string& ip)
{
	inValidIPs_.emplace(ip);
}