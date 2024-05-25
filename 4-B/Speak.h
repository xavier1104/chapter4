#pragma once

class Speak
{
public:
	Speak(string content);
	~Speak();

	string GetContent() { return content_; }
private:
	string content_;
};