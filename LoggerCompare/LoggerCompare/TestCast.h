#pragma once
#include <vector>
#include "LogMsg.h"
#include "TestReport.h"

using namespace std;

class TestCase
{
public:
	TestCase(void);
	~TestCase(void);

	
	void GetRecordLog(char* path);
	void GetPlaybackLog(char* path);
	void Compare();
	void SetXMLReportPath(char* path)
	{
		xmlPath.assign(path);
	}
	void SetHTMLReportPath(char* path)
	{
		htmlPath.assign(path);
	}
	
private:
	vector<LogMsg*> recordList;
	vector<LogMsg*> playbackList;
	vector<string> threadName;
	vector<TestReport *> reportList;

	char* filepath;
	string xmlPath;
	string htmlPath;

	int rightCount;
	int wrongCount;
	int ExceptionCount;

	int numd;
	int posd;
	int cnum;

	void GetPlaybackFile(char* path);
	LogMsg* GetLogMsg(char* buffer);
	void RecordSort();
	void PlaybackSort();
	void CreateReportXML(char* path);
	void CreateReportHTML(char* path);
	void CreateTestReport();
	void ClearPlaybackLog();
	void ClearTestReport();
};

