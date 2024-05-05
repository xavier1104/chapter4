#pragma once

class BlackListException : public exception
{
public:
	BlackListException(string host);
	~BlackListException();

	virtual const char* what() const throw();

private:
	string host_;
};