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
	void CreateReportXML(char* path);
	void CreateReportHTML(char* path);

private:
	vector<LogMsg*> recordList;
	vector<LogMsg*> playbackList;
	vector<string> threadName;
	vector<TestReport *> reportList;

	int rightCount;
	int wrongCount;
	int ExceptionCount;

	LogMsg* GetLogMsg(char* buffer);
	void RecordSort();
	void PlaybackSort();
};

