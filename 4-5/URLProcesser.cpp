#include "stdafx.h"
#include "HttpClient.h"
#include "URLProcesser.h"

URLProcesser::URLProcesser(shared_ptr<HttpClient> httpClient)
	:httpClient_(httpClient)
{
}

URLProcesser::~URLProcesser()
{
}
