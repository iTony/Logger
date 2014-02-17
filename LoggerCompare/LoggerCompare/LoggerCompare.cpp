// LoggerCompare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestCast.h"

int main(int argc, char* argv[])
{
	if (argc <3)
	{
		printf("please input RecordLog, PlaybackLog,XMLReportPath,HTMLReportPath");
		return -1;
	}
	//printf("%d\n",argc);
	TestCase tc ;
	
	char * rlog = (char *)argv[1];

	tc.GetRecordLog((char *)argv[1]);
	tc.GetPlaybackLog((char *)argv[2]);
	tc.SetXMLReportPath((char *)argv[3]);
	if (argc == 5)
	{
		tc.SetHTMLReportPath((char *)argv[4]);
	}
	
	
	tc.Compare();
	
	//delete tc;
	return 0;
}

