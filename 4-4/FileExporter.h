#pragma once

class FileExporter : public Exporter
{
public:
	FileExporter(string filename);
	~FileExporter();

	void Export(string msg) override;

private:
	string filename_;
};