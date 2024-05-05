#pragma once

class RequestFailException : public exception
{
public:
	RequestFailException(string url);
	~RequestFailException();
	
	virtual const char* what() const throw();
	string GetFailUrl() const throw() { return url_; }

private:
	string url_;
};