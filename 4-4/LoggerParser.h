#pragma once

class LoggerParser
{
public:
	static void Parse(string filename);
	
private:
	static shared_ptr<Logger> ParseLogger(const Value& value, string name, shared_ptr<Logger> parent);
	static shared_ptr<Exporter> ParseExporter(const Value& value);
};