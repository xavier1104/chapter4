#pragma once

class ConsoleExporter : Exporter
{
public:
	ConsoleExporter();
	~ConsoleExporter();

	void Export(string msg) override;
};