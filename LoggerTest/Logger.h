#include <string>
#include <Windows.h>
using namespace std;

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGGER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGGER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

class LOGGER_API Logger {
public:
	static Logger* GetLogger();
	void AddThread(string name);

	//void Init();
	void Init(string path);
	void Init(string path,string softwarename);
	void Init(string path,int maxBuf);
	void Init(string path,string softwareName,int maxBuf);
	void Run();
	void Debug(string className,string funName,string message);
	void Info(string className,string funName,string message);
	void Warn(string className,string funName,string message);
	void Error(string className,string funName,string message);
	void Finish();

private:
	//static ofstream fout;
	//static int maxBuffer;
	//static int count;
	//static map<int,string> threadMap;
	static Logger* m_logger;
	//static string filePath;
	//static HANDLE m_mutex;
	static HANDLE m_InitMutex;
	//LogInfo logInfo;

	Logger(void);
	//string GetTime();
	//void SetFilePath(string path);
	//void SetMaxBuffer(int count);
	//void Add(string level,string className,string funName,string message);
	// TODO: add your methods here.
};