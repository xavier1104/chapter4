#pragma once

class Post
{
public:
	Post(string id, string title, string content, vector<string> tags);
	~Post();

	string GetContent() { return content_; }
	string GetTitle() { return title_; }
	vector<string> GetTags() { return tags_; }
private:
	string id_;
	string title_;
	string content_;
	vector<string> tags_;
};