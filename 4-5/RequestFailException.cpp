#include "stdafx.h"
#include "RequestFailException.h"

RequestFailException::RequestFailException(string url)
	:url_(url)
{
}

RequestFailException::~RequestFailException()
{
}

const char* RequestFailException::what() const throw()
{
	string msg("Invalid URL:" + url_);
	return msg.c_str();
}
