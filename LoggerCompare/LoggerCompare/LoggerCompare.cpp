// LoggerCompare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestCast.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TestCase tc ;
	tc.GetRecordLog("E:\\Test\\Log\\csharplog.txt");
	tc.GetPlaybackLog("E:\\Test\\Log\\csharplog%2014012014t%000d.txt");
	tc.SetHTMLReportPath("E:\\Test\\Log\\Report");
	tc.SetXMLReportPath("E:\\Test\\Log\\Report");

	tc.Compare();
	
	//delete tc;
	return 0;
}

