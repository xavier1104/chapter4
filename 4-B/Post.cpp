#include "stdafx.h"
#include "Post.h"

Post::Post(string id, string title, string content, vector<string> tags)
	:id_(id)
	,title_(title)
	,content_(content)
	,tags_(tags)
{
}

Post::~Post()
{
}
