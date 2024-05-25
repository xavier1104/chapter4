#pragma once
#include "stdafx.h"

static string GetTagStr(vector<string> tags)
{
	string str = "";
	for (int i = 0; i < tags.size(); ++i) {
		str += '@' + tags.at(i);
		if (i < tags.size() - 1) {
			str += ", ";
		}
	}

	return str;
}

static bool HasTag(vector<string>& tags, string match)
{
	for (string& tag : tags) {
		if (tag == match) {
			return true;
		}
	}

	return false;
}