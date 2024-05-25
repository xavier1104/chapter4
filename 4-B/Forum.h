#pragma once

class Member;
class Post;
class Comment;
class Forum
{
public:
	Forum();
	~Forum();

	void SendPost(string senderId, shared_ptr<Post> post);
	void AddComment(string senderId, shared_ptr<Comment> comment);
};