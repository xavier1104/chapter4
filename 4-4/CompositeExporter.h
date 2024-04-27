#pragma once

class CompositeExporter : Exporter
{
public:
	CompositeExporter(vector<shared_ptr<Exporter>> exporters);
	~CompositeExporter();

	void Export(string msg) override;
private:
	vector<shared_ptr<Exporter>> exporters_;
};