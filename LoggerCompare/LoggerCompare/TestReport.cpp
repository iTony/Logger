#include "StdAfx.h"
#include "TestReport.h"


TestReport::TestReport(void)
{
}

TestReport::TestReport(string level,string info,string recordMsg,string playbackMsg,string testResult)
{
	this->level = level;
	this->info = info;
	this->recordMsg = recordMsg;
	this->playbackMsg = playbackMsg;
	this->testResult = testResult;
}

TestReport::TestReport(string level,string clsName,string funName,string thread,string recordMsg,string playbackMsg,string testResult)
{
	this->level = level;
	this->clsName = clsName;
	this->funName = funName;
	this->thread = thread;
	this->recordMsg = recordMsg;
	this->playbackMsg = playbackMsg;
	this->testResult = testResult;
}

TestReport::~TestReport(void)
{
}
