#include "stdafx.h"
#include "Comment.h"

Comment::Comment(string postId, string content, vector<string> tags)
	:content_(content)
	,tags_(tags)
	,postId_(postId)
{
}

Comment::~Comment()
{
}
