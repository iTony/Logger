#include <fstream>
#include <map>
#include <string>
#include <windows.h>

using namespace std;
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGGERCORE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGGERCORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LOGGERCORE_EXPORTS
#define LOGGERCORE_API extern "C" __declspec(dllexport)
#else
#define LOGGERCORE_API extern "C" __declspec(dllimport)
#endif

string time;
string libVersion;
string softwareName;
string osInfo;
string filePath;
ofstream fout;
int maxBuffer = 10;
int count = 0;
map<int,string> threadMap;
HANDLE m_mutex;

void InitCore();
void PathParse(const char* path);
void Add(string className,string funName,int lineNum,string message);
string GetTime();
string GetOSVer();
string InfoVersionWinEx();
string InfoVersionWin();
string InfoVersion64bit();

string GetDllVersion();

LOGGERCORE_API void __stdcall AddThreadCore(const char* name);
LOGGERCORE_API void __stdcall InitCore1(const char* fpath,const char* swname);
LOGGERCORE_API void __stdcall InitCore2(const char* fpath,const char* swname,int mb);
LOGGERCORE_API void __stdcall RunCore();
LOGGERCORE_API void __stdcall DebugCore(const char* className,const char* funName,int lineNum,const char* message);
LOGGERCORE_API void __stdcall InfoCore(const char* className,const char* funName,int lineNum,const char* message);
LOGGERCORE_API void __stdcall WarnCore(const char* className,const char* funName,int lineNum,const char* message);
LOGGERCORE_API void __stdcall ErrorCore(const char* className,const char* funName,int lineNum,const char* message);
LOGGERCORE_API void __stdcall FinishCore();
