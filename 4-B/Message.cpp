#include "stdafx.h"
#include "Message.h"

Message::Message(string& content, vector<string> tags)
	:content_(content)
	, tags_(tags)
{
}

Message::~Message()
{
}
