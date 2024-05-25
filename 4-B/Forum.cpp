#include "stdafx.h"
#include "Member.h"
#include "Post.h"
#include "utility.h"
#include "Comment.h"
#include "Forum.h"

Forum::Forum()
{
}

Forum::~Forum()
{
}

void Forum::SendPost(string senderId, shared_ptr<Post> post)
{
	cout << senderId << ": 【" << post->GetTitle() << "】" << post->GetContent() << " " << GetTagStr(post->GetTags()) << '\n';
}

void Forum::AddComment(string senderId, shared_ptr<Comment> comment)
{
	if (senderId == "bot") {
		cout << "🤖: comment in post " << comment->GetPostId() << ": " << comment->GetContent() << " " << GetTagStr(comment->GetTags()) << '\n';
	}
}
