// LoggerCompare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestCast.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TestCase tc ;
	tc.GetRecordLog("log.txt");
	tc.GetPlaybackLog("log1.txt");
	tc.Compare();
	tc.CreateReportXML("report.xml");
	tc.CreateReportHTML("report.html");
	//delete tc;
	return 0;
}

