// LoggerTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#pragma comment(lib,"Logger")

DWORD WINAPI ThreadFun(LPVOID pM)  
{  
	Logger *logger = Logger::GetLogger();
	int num = (int)pM;
	//string str(num);
	char a[32];
	itoa(num, a, 32);
	string str(a);
	logger->AddThread("Thread"+str);
	//Logger logger = Logger::GetLogger("log1.txt");
	int id = GetCurrentThreadId();
	char msg[256];
	for (int i=0;i<10;i++)
	{
		memset(msg,0,256);
		sprintf(msg,"子线程输出Hello World%d\n",i);
		logger->Debug("NULL","ThreadFun",msg);
		Sleep(10);
		logger->Info("NULL","ThreadFun","Hello World");
		logger->Warn("NULL","ThreadFun","WarnTest");
		logger->Error("NULL","ThreadFun","ErrorTest");
	}
	
	return 0;  
}  

void ThreadLogTest()
{
	Logger *logger = Logger::GetLogger();
	logger->Info("NULL","_tmain","Hello World");
	//Logger logger = Logger.GetLogger("log");
	HANDLE handle1 = CreateThread(NULL, 0, ThreadFun, (LPVOID)1, 0, NULL);
	HANDLE handle2 = CreateThread(NULL, 0, ThreadFun, (LPVOID)2, 0, NULL);
	//HANDLE handle3 = CreateThread(NULL, 0, ThreadFun, (LPVOID)3, 0, NULL);
	//HANDLE handle4 = CreateThread(NULL, 0, ThreadFun, (LPVOID)4, 0, NULL);
	//getchar();
	WaitForSingleObject(handle1,INFINITE);
	WaitForSingleObject(handle2,INFINITE);
	//WaitForSingleObject(handle3,INFINITE);
	//WaitForSingleObject(handle4,INFINITE);
	//logger->Finish();
}

int _tmain(int argc, _TCHAR* argv[])
{
	Logger *logger = Logger::GetLogger();

	//LogInfo info("log.txt");
	//info.SetFilePath("log.txt");
	logger->Init("E:\\Test\\Log\\cpplog%t%d.txt");
	//logger->SetFilePath("log.txt");
	logger->Run();

	logger->Debug("NULL","_tmain","hello world");
	logger->Info("NULL","_tmain","infomation");
	ThreadLogTest();
	logger->Finish();
	//getchar();
	return 0;
}

