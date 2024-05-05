#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"
#include "RequestFailException.h"
#include "ServiceDiscoverProcesser.h"

ServiceDiscoverProcesser::ServiceDiscoverProcesser(shared_ptr<HttpClient> httpClient)
	:URLProcesser(httpClient)
{
	LoadConfig("config.txt");
}

ServiceDiscoverProcesser::~ServiceDiscoverProcesser()
{
}

void ServiceDiscoverProcesser::Send(vector<string>& urls)
{
	vector<string> discoveredUrls;
	for (string& url : urls) {
		vector<string> replacedUrls = ReplacedUrls(url);
		for (string& replacedUrl : replacedUrls) {
			discoveredUrls.emplace_back(replacedUrl);
		}

		if (replacedUrls.size() == 0) {
			discoveredUrls.emplace_back(url);
		}
	}

	try {
		httpClient_->Send(discoveredUrls);
	}
	catch (const RequestFailException& e) {
		cerr << e.what() << '\n';
		AddInvalid(e.GetFailUrl());
	}
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
			auto&& it = find(inValidIPs_.begin(), inValidIPs_.end(), ip);
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

void ServiceDiscoverProcesser::LoadConfig(string filename)
{
	config_.clear();

	ifstream f(filename);
	if (f.fail()) {
		cout << "Load " << filename << " failed\n";
	}

	string line;
	while (!f.eof()) {
		getline(f, line);

		istringstream ss(line);
		string token;
		vector<string> tokens;
		while (getline(ss, token, ':')) {
			tokens.emplace_back(token);
		}

		if (tokens.size() != 2) {
			cout << "Config format err\n";
			continue;
		}

		string host = tokens[0];

		ss.clear();
		ss.str(tokens[1]);

		tokens.clear();
		while (getline(ss, token, ',')) {
			tokens.emplace_back(token);
		}

		for (auto& ip : tokens) {
			config_[host].emplace_back(ip);
		}
	}
}

void ServiceDiscoverProcesser::AddInvalid(string url)
{
	size_t begin = url.find("//");
	if (begin == string::npos) {
		return;
	}

	size_t end = url.find("/", begin + 2);
	if (end == string::npos) {
		return;
	}

	begin = begin + 2;
	string invalidIP = url.substr(begin, (end - begin));
	for (auto&& [host, ips] : config_) {
		for (auto& ip : ips) {
			if (invalidIP == ip) {
				inValidIPs_.emplace_back(ip);
			}
		}
	}

	if (inValidIPs_.size() > 1) {
		inValidIPs_.pop_front();
	}
}