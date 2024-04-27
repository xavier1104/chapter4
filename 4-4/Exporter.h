#pragma once

class Exporter
{
public:
	Exporter();
	~Exporter();

	virtual void Export(string msg) = 0;
};