#pragma once

class FileExporter : Exporter
{
public:
	FileExporter(string filename);
	~FileExporter();

	void Export(string msg) override;

private:
	string filename_;
};