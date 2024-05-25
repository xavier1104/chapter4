#pragma once

class Message
{
public:
	Message(string& content, vector<string> tags = {});
	~Message();
	
	string GetContent() { return content_; }
	vector<string> GetTags() { return tags_; }

private:
	string content_;
	vector<string> tags_;
};