#pragma once

class Comment
{
public:
	Comment(string postId, string content, vector<string> tags);
	~Comment();

	string GetPostId() { return postId_; }
	string GetContent() { return content_; }
	vector<string> GetTags() { return tags_; }
private:
	string postId_;
	string content_;
	vector<string> tags_;
};