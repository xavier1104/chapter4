#pragma once

class Exporter;
class Layout;
class Logger : public enable_shared_from_this<Logger>
{
public:
	enum LEVEL
	{
		NONE = 0,
		TRACE,
		INFO,
		DEBUG,
		WARN,
		ERROR
	};

public:
	Logger(string name, LEVEL level, shared_ptr<Logger> parent, shared_ptr<Layout> layout, shared_ptr<Exporter> exporter);
	~Logger();

	string GetName() { return name_; }
	LEVEL GetLevel() { return level_; }
	shared_ptr<Layout> GetLayout() { return layout_; }
	shared_ptr<Exporter> GetExporter() { return exporter_; }

	void Write(LEVEL level, string content);

	static string GetLevelStr(LEVEL level);
	static LEVEL GetLevelByStr(string level);

private:
	string name_;
	LEVEL level_;
	shared_ptr<Logger> parent_;
	shared_ptr<Layout> layout_;
	shared_ptr<Exporter> exporter_;
};