#include "StdAfx.h"
#include "LogMsg.h"


LogMsg::LogMsg(void)
{
}

LogMsg::LogMsg(string time,string level,string clsName,string funName,string thread,string msg)
{
	this->time = time;
	this->level = level;
	this->clsName = clsName;
	this->funName = funName;
	this->thread = thread;
	this->message = msg;
}

LogMsg::~LogMsg(void)
{
}
