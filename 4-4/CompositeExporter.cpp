#include "stdafx.h"
#include "Exporter.h"
#include "CompositeExporter.h"

CompositeExporter::CompositeExporter(vector<shared_ptr<Exporter>> exporters)
	:exporters_(exporters)
{
}

CompositeExporter::~CompositeExporter()
{
}

void CompositeExporter::Export(string msg)
{
	for (auto& exporter : exporters_) {
		exporter->Export(msg);
	}
}
