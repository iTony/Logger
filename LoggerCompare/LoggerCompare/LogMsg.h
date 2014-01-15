#pragma once

#include <string>

using namespace std;

class LogMsg
{
public:
	LogMsg(string time,string level,string clsName,string funName,string thread,string message);
	LogMsg(void);
	~LogMsg(void);

	string GetThread()
	{
		return thread;
	}
	string GetTime()
	{
		return time;
	}
	string GetLevel()
	{
		return level;
	}
	string GetClsName()
	{
		return clsName;
	}
	string GetFunName()
	{
		return funName;
	}
	string GetMessage()
	{
		return message;
	}
private:
	string time;
	string level;
	string clsName;
	string funName;
	string thread;
	string message;
};

