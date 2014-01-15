#pragma once
#include <string>
#include <list>
#include "LogMsg.h"

using namespace std;

class TestReport
{
public:
	TestReport(void);
	TestReport(string level,string info,string recordMsg,string playbackMsg,string testResult);
	TestReport(string level,string clsName,string funName,string thread,string recordMsg,string playbackMsg,string testResult);
	~TestReport(void);

	string GetLevel()
	{
		return level;
	}
	string GetInfo()
	{
		return info;
	}
	string GetClassName()
	{
		return clsName;
	}
	string GetFunName()
	{
		return funName;
	}
	string GetThread()
	{
		return thread;
	}
	string GetRecordMsg()
	{
		return recordMsg;
	}
	string GetPlaybackMsg()
	{
		return playbackMsg;
	}
	string GetTestResult()
	{
		return testResult;
	}

private:
	string level;
	string info;
	string clsName;
	string funName;
	string thread;
	string recordMsg;
	string playbackMsg;
	string testResult;
};