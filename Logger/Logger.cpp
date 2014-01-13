// Logger.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Logger.h"
#include "LoggerCore.h"
#include "Lock.h"

#pragma comment(lib,"LoggerCore")

Logger* Logger::m_logger = 0;
HANDLE Logger::m_InitMutex;

Logger::Logger()
{

}

Logger* Logger::GetLogger()
{
	if (m_logger==NULL)
	{
		Lock lock(m_InitMutex);
		if (m_logger == NULL)
		{
			m_logger = new Logger();
			return m_logger;
		}
		else return m_logger;
		lock.UnLock();

	}
	else return m_logger;
}

void Logger::Init(string path)
{
	//string libVersion = GetDllVersion();
	InitCore1(path.c_str(),"");
}
void Logger::Init(string path,string softwarename)
{
	//string libVersion = GetDllVersion();
	InitCore1(path.c_str(),softwarename.c_str());
}
void Logger::Init(string path,int maxBuf)
{
	//string libVersion = GetDllVersion();
	InitCore2(path.c_str(),"",maxBuf);
}

void Logger::Init(string path,string softwareName,int maxBuf)
{
	//string libVersion = GetDllVersion();
	InitCore2(path.c_str(),softwareName.c_str(),maxBuf);
}

void Logger::Run()
{
	RunCore();
}

void Logger::AddThread(string name)
{
	AddThreadCore(name.c_str());
}

void Logger::Debug(string className,string funName,string message)
{
	DebugCore(className.c_str(),funName.c_str(),0,message.c_str());
}

void Logger::Info(string className,string funName,string message)
{
	InfoCore(className.c_str(),funName.c_str(),0,message.c_str());
}

void Logger::Warn(string className,string funName,string message)
{
	WarnCore(className.c_str(),funName.c_str(),0,message.c_str());
}

void Logger::Error(string className,string funName,string message)
{
	ErrorCore(className.c_str(),funName.c_str(),0,message.c_str());
}

void Logger::Finish()
{
	FinishCore();
}