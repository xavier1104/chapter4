#include "stdafx.h"
#include "BlackListException.h"

BlackListException::BlackListException(string host)
	:host_(host)
{
}

BlackListException::~BlackListException()
{
}

const char* BlackListException::what() const throw()
{
	string msg("Host: " + host_ + " in black list!");
	return msg.c_str();
}
