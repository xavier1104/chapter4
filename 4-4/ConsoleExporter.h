#pragma once

class ConsoleExporter : public Exporter
{
public:
	ConsoleExporter();
	~ConsoleExporter();

	void Export(string msg) override;
};