#include "stdafx.h"
#include "Exporter.h"
#include "ConsoleExporter.h"

ConsoleExporter::ConsoleExporter()
{
}

ConsoleExporter::~ConsoleExporter()
{
}

void ConsoleExporter::Export(string msg)
{
	cout << msg << '\n';
}
