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
	fstream f(filename_);
	if (f.fail()) {
		cout << "File:" << filename_ << " open failed!\n";
		return;
	}

	filename_.append(msg);
	f.close();
}
