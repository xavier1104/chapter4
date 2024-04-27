#include "stdafx.h"
#include "Exporter.h"
#include "FileExporter.h"

FileExporter::FileExporter(string filename)
	:filename_(filename)
{
}

FileExporter::~FileExporter()
{
}

void FileExporter::Export(string msg)
{
	ofstream f(filename_, ios::app);
	if (f.fail()) {
		cout << "File:" << filename_ << " open failed!\n";
		return;
	}

	f << msg;
	f.close();
}
