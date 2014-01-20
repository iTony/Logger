// LoggerCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LoggerCore.h"
#include <stdio.h>
#include <io.h>

#pragma comment(lib, "version.lib")
bool IsWinNT = false;
bool IsWinNT6 = false;
bool IsWinVista = false;
bool IsWin2008 = false;
bool IsWin7 = false;
bool IsWin8 = false;
bool IsWinNT5 = false;
bool IsWin2K = false;
bool IsWinServer = false;
bool IsWinXP = false;
bool IsWin2003 = false;
bool IsWinHomeServer = false;
bool IsWin64bit = false;
bool IsWinMediaCenter = false;
bool IsWin9x = false;
bool IsWin95 = false;
bool IsWin98SE = false;
bool IsWin98 = false;
bool IsWin98ME = false;
bool IsWinNT3 = false;
bool IsWinNT4 = false;
bool IsWin32s = false;

typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

LOGGERCORE_API void __stdcall AddThreadCore(const char* name)
{
	string n(name);
	int id = GetCurrentThreadId();
	threadMap.insert(map<int,string>::value_type(id,n));
}

void PathParse(const char *path)
{
	//printf("%d,path:%s\n",strlen(path),path);
	bool flag = false;
	char* pos = (char *)path;
	int index = 0;
	int num = 0;
	int count = 0;
	int numpos = 0;

	char d[10];
	memset(d,0,strlen(d));
	int dpos = 0;
	//tring path = filePath;
	char tmp[MAX_PATH];
	memset(tmp,0,strlen(tmp));
	char time[15];
	memset(time,0,strlen(time));
	int size = strlen(path);
	for (int i=0;i<size;i++)
	{

		if (pos[i]=='%')
		{
			flag = true;
			i++;
			if (pos[i]=='t')
			{
				SYSTEMTIME sys;
				GetLocalTime( &sys );
				sprintf(time,"%4d%02d%02d%02d%02d%02d\0",
					sys.wYear,sys.wMonth, sys.wDay, sys.wHour, sys.wMinute,sys.wSecond);
				for(int j=0;j<strlen(time);j++)
				{
					tmp[index] = time[j];
					index++;
				}
			}
			else if (pos[i]=='d')
			{
				if (dpos ==0)
				{
					numpos = index;
					tmp[index] = '0';
					index++;
					count++;
				}
				else
				{
					num = atoi(d);
					count = strlen(d);
					for(int j=0;j<dpos;j++)
					{
						tmp[index] = d[j];
						index++;
					}
				}
			}
			else if (pos[i]<='9'&&pos[i]>='0')
			{
				numpos = index;
				while(1)
				{
					if (pos[i]=='d')
					{
						break;
					}
					tmp[index]=pos[i];
					index++;
					d[dpos] = pos[i];
					dpos++;
					i++;
				}
				
			}
		}
		else
		{
			tmp[index]=pos[i];
			index++;
		}
	}
	//fout.open(tmp);
	//printf("%d\n",index);
	tmp[index] = '\0';
	while ((access( tmp, 0 )) != -1&&flag)
	{
		num++;
		itoa(num,d,10);
		if (dpos==0||dpos<strlen(d))
		{
			char t[128];
			memset(t,0,strlen(t));
			int tc = 0;
			for (int i=0;i<strlen(tmp);i++)
			{
				if (i==numpos)
				{
					for (int j=0;j<strlen(d);j++)
					{
						t[tc] = d[j];
						tc++;
						
					}
					for (int j=0;j<count;j++)
					{
						i++;
					}
					
				}
				t[tc] = tmp[i];
				tc++;
			}
			memset(tmp,0,strlen(tmp));
			for (int i=0;i<tc;i++)
			{
				tmp[i] = t[i];
			}
			tmp[tc]='\0';
			count = strlen(d);
			//fout.open(t);
		}
		else
		{
			int j=0;
			for(int i=dpos-strlen(d);i<dpos;i++)
			{
				tmp[numpos+i]=d[j];
				j++;
			}
			//fout.open(tmp);
		}
	}
	//printf("%d,tmp:%s",strlen(tmp),tmp);
	fout.open(tmp);
}

void InitCore()
{
	//printf("init\n");
	if (softwareName == "")
	{
		TCHAR szFullPath[MAX_PATH];
		GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
		char * ch=new char[MAX_PATH];
		WideCharToMultiByte(CP_OEMCP,NULL,szFullPath,-1,ch,sizeof(szFullPath),NULL,FALSE);
		
		softwareName.append(ch);

		int index = softwareName.rfind("\\");
		string sub = softwareName.substr(index+1);
		softwareName = sub;
	}
	m_mutex = ::CreateMutex(NULL, FALSE, NULL);
	time = GetTime();
	osInfo = GetOSVer();
	//libVersion = GetDllVersion();
	libVersion.assign("1.0.0.1");
	//libVersion = GetDllVersion("LoggerCore.dll");
}

LOGGERCORE_API void __stdcall InitCore1(const char* fpath,const char* swname)
{
	PathParse(fpath);
	//libVersion += libver;
	filePath += fpath;
	softwareName += swname;
	//printf("path:%s, name:%s\n",fpath,swname);
	InitCore();
}

LOGGERCORE_API void __stdcall InitCore2(const char* fpath,const char* swname,int mb)
{
	PathParse(fpath);
	filePath += fpath;
	softwareName += swname;
	maxBuffer = mb;
	InitCore();
}

LOGGERCORE_API void __stdcall RunCore()
{
	//remove(filePath.c_str());
// 	fstream _file;
// 	_file.open(filePath,ios::in);
// 	if (_file)
// 	{
// 		if ()
// 		{
// 			printf("remove file success");
// 		}
// 		else
// 		{
// 			printf("remove file fail");
// 		}
// 	}
	//fout.open(filePath);
	
	//printf("filepath: %s\n",filePath.c_str());
	char info[512];
	memset(info,0,sizeof(info));
	sprintf(info,"%s [%s] [%s] [%s]\n",time.c_str(),libVersion.c_str(),softwareName.c_str(),osInfo.c_str());
	fout<<info;
	//printf("Run");
	
}

void Add(string level,string className,string funName,int lineNum,string message)
{
	string time = GetTime();

	int id = GetCurrentThreadId();
	map<int,string>::iterator it = threadMap.find(id);
	string threadName;
	if (it == threadMap.end())
	{
		threadName = "MainThread";
	}
	else
	{
		threadName = it->second;
	}
	int index = message.rfind("\n");
	if (index!=message.length()-1)
	{
		message+="\n";
	}

	char msg[1024];
	memset(msg,0,1024);
	if (lineNum==0)
	{
		sprintf(msg,"%s %s [%s] %s(%s) %s",
			time.c_str(),level.c_str(),threadName.c_str(),className.c_str(),funName.c_str(),message.c_str());
	}
	else
	{
		sprintf(msg,"%s %s [%s] %s(%s,%d) %s",
			time.c_str(),level.c_str(),threadName.c_str(),className.c_str(),funName.c_str(),lineNum,message.c_str());
	}
	

	WaitForSingleObject(m_mutex,INFINITE);
	fout<<msg;
	count++;
	if (count>=maxBuffer)
	{
		fout.flush();
		count = 0;
	}
	ReleaseMutex(m_mutex);
}

LOGGERCORE_API void __stdcall DebugCore(const char* className,const char* funName,int lineNum,const char* message)
{
	Add("Debug",className,funName,lineNum,message);
	//printf("Debug: %s\n",message);
}

LOGGERCORE_API void __stdcall InfoCore(const char* className,const char* funName,int lineNum,const char* message)
{
	Add("Info",className,funName,lineNum,message);
	//printf("Info: %s\n",message);
}

LOGGERCORE_API void __stdcall WarnCore(const char* className,const char* funName,int lineNum,const char* message)
{
	Add("Warn",className,funName,lineNum,message);
	//printf("Warn: %s\n",message);
}

LOGGERCORE_API void __stdcall ErrorCore(const char* className,const char* funName,int lineNum,const char* message)
{
	Add("Error",className,funName,lineNum,message);
	//printf("Error: %s\n",message);
}

LOGGERCORE_API void __stdcall FinishCore()
{
	fout.flush();
	fout.close();
	//printf("Finish\n");
}

string GetTime()
{
	char time[28];
	memset(time,0,28);
	SYSTEMTIME sys;
	GetLocalTime( &sys );
	sprintf(time,"%4d-%02d-%02d %02d:%02d:%02d.%03d",
		sys.wYear,sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond,sys.wMilliseconds);

	string str(time);
	return str;
}

string GetOSVer()
{
	OSVERSIONINFO   osver;
	osver.dwOSVersionInfoSize   =   sizeof(OSVERSIONINFO);     
	GetVersionEx(&osver);
	if(osver.dwMajorVersion>=4&&osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		return InfoVersionWinEx();
	}
	else
		return InfoVersionWin();
}

string InfoVersionWinEx()
{
	OSVERSIONINFOEX OSinfo;
	string strWindowsVersion="";
	SYSTEM_INFO SysInfo;
	long RetValue;
	DWORD RetProdType;
	OSinfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	RetValue=GetVersionEx((LPOSVERSIONINFO)&OSinfo);
	PGPI pGPI;
	//PGPI pGPI = (PGPI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
	if(1)
	{
		IsWinNT=true;
		switch(OSinfo.dwMajorVersion)
		{
		case 6:
			pGPI = (PGPI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
			IsWinNT6=true;
			switch(OSinfo.dwMinorVersion)
			{
			case 0:
				if(OSinfo.wProductType == VER_NT_WORKSTATION)
				{
					IsWinVista=true;
					strWindowsVersion="Windows Vista";
				}
				else
				{
					IsWin2008=true;
					strWindowsVersion="Windows Server 2008";
				}
				break;
			case 1:
				{
					IsWin7=true;
					if(OSinfo.dwBuildNumber==6801)
					{
						strWindowsVersion="Windows 7 preBeta build M3 PDC 2008";
					}
					else
					{
						strWindowsVersion="Windows 7";
					}
				}
				break;
			case 2:
				IsWin8=true;
				if(OSinfo.dwBuildNumber==7867)
					strWindowsVersion="Windows 8 Milestone1";
				else if(OSinfo.dwBuildNumber<=7947&&OSinfo.dwBuildNumber>=7910)
					strWindowsVersion="Windows 8 Milestone2";
				else if(OSinfo.dwBuildNumber==7955)
					strWindowsVersion="Windows 8 Milestone3";
				else
					strWindowsVersion="Windows 8";
				break;
			default:
				char temp[10];
				strWindowsVersion="Windows NT v";
				_itoa_s(OSinfo.dwMajorVersion,temp,sizeof(temp),10);
				strWindowsVersion.append(temp);
				//strWindowsVersion.append("Windows NT v%d",OSinfo.dwMajorVersion);
				break;
			}
			strWindowsVersion += InfoVersion64bit();
			//GetProductInfo(OSinfo.dwMajorVersion, OSinfo.dwMinorVersion, OSinfo.wServicePackMajor, OSinfo.wServicePackMinor, (PDWORD)&RetProdType);

			pGPI( OSinfo.dwMajorVersion, OSinfo.dwMinorVersion,  OSinfo.wServicePackMajor, OSinfo.wServicePackMinor, &RetProdType);
			switch(RetProdType)
			{
			case PRODUCT_BUSINESS:
				strWindowsVersion+=" Business";
				break;
			case PRODUCT_BUSINESS_N:
				strWindowsVersion+=" Business N";
				break;
			case PRODUCT_CLUSTER_SERVER:
				strWindowsVersion+=" HPC";
				break;
			case PRODUCT_DATACENTER_SERVER:
				strWindowsVersion+=" Datacenter";
				break;
			case PRODUCT_DATACENTER_SERVER_CORE:
				strWindowsVersion +=" Datacenter (core installation)";
				break;
			case PRODUCT_DATACENTER_SERVER_CORE_V:
				strWindowsVersion +=" Datacenter sans Hyper-V(core installation)";
				break;
			case PRODUCT_DATACENTER_SERVER_V:
				strWindowsVersion += " Datacenter sans Hyper-V";
				break;
			case PRODUCT_ENTERPRISE:
				strWindowsVersion += " Enterprise";
				break;
			case PRODUCT_ENTERPRISE_N:
				strWindowsVersion += " Enterprise N";
				break;
			case PRODUCT_ENTERPRISE_SERVER:
				strWindowsVersion += " Server Enterprise";
				break;
			case PRODUCT_ENTERPRISE_SERVER_CORE:
				strWindowsVersion += " Server Enterprise (core installation)";
				break;
			case PRODUCT_ENTERPRISE_SERVER_CORE_V:
				strWindowsVersion += " Server Enterprise sans Hyper-V(core installation)";
				break;
			case PRODUCT_ENTERPRISE_SERVER_IA64:
				strWindowsVersion += " Enterprise pour Itanium";
				break;
			case PRODUCT_ENTERPRISE_SERVER_V:
				strWindowsVersion += " Server Enterprise sans Hyper-V";
				break;
			case PRODUCT_HOME_BASIC:
				strWindowsVersion += " Home Basic";
				break;
			case PRODUCT_HOME_BASIC_N:
				strWindowsVersion += " Home Basic N";
				break;
			case PRODUCT_HOME_PREMIUM:
				strWindowsVersion += " Home Premium";
				break;
			case PRODUCT_HOME_PREMIUM_N:
				strWindowsVersion += " Home Premium N";
				break;
			case PRODUCT_HYPERV:
				strWindowsVersion += " Microsoft Hyper-V Server";
				break;
			case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT:
				strWindowsVersion += " Essential Business Server Management Server";
				break;
			case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING:
				strWindowsVersion += " Essential Business Server Messaging Server";
				break;
			case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY:
				strWindowsVersion += " Essential Business Server Security Server";
				break;
			case PRODUCT_SERVER_FOR_SMALLBUSINESS:
				strWindowsVersion += " Windows Essential Server Solutions";
				break;
			case PRODUCT_SERVER_FOR_SMALLBUSINESS_V:
				strWindowsVersion += " Windows Essential Server Solutions sans Hyper-V";
				break;
			case PRODUCT_SMALLBUSINESS_SERVER:
				strWindowsVersion += " Small Business Server";
				break;
			case PRODUCT_STANDARD_SERVER:
				strWindowsVersion += " Standard";
				break;
			case PRODUCT_STANDARD_SERVER_CORE:
				strWindowsVersion += " Standard (core installation)";
				break;
			case PRODUCT_STANDARD_SERVER_CORE_V:
				strWindowsVersion += " Standard sans Hyper-V(core installation)";
				break;
			case PRODUCT_STANDARD_SERVER_V:
				strWindowsVersion += " Standard sans Hyper-V";
				break;
			case PRODUCT_STARTER:
				strWindowsVersion += " Starter";
				break;
			case PRODUCT_STORAGE_ENTERPRISE_SERVER:
				strWindowsVersion += " Storage Server Enterprise";
				break;
			case PRODUCT_STORAGE_EXPRESS_SERVER:
				strWindowsVersion += " Storage Server Express";
				break;
			case PRODUCT_STORAGE_STANDARD_SERVER:
				strWindowsVersion += " Storage Server Standard";
				break;
			case PRODUCT_STORAGE_WORKGROUP_SERVER:
				strWindowsVersion += " Storage Server Workgroup";
				break;
			case PRODUCT_ULTIMATE:
				strWindowsVersion += " Ultimate";
				break;
			case PRODUCT_ULTIMATE_N:
				strWindowsVersion += " Ultimate N";
				break;
			case PRODUCT_WEB_SERVER:
				strWindowsVersion += " Web Server";
				break;
			case PRODUCT_WEB_SERVER_CORE:
				strWindowsVersion += " Web Server(core installation)";
				break;
			case PRODUCT_UNDEFINED:
				strWindowsVersion += " Produit inconnu";
				break;

			}
			// 			strWindowsVersion.append("(");
			// 			strWindowsVersion.append(InfoVersionMediaCenter());
			// 			strWindowsVersion.append(")");
			break;
		case 5:
			IsWinNT5=true;
			switch(OSinfo.dwMinorVersion)
			{
			case 0:
				IsWin2K=true;
				strWindowsVersion = "Windows 2000";
				if(OSinfo.wProductType==VER_NT_WORKSTATION)
					if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_PERSONAL)
						strWindowsVersion += " Home Edition";
					else
						strWindowsVersion += " Professionel";
				else
				{
					IsWinServer=true;
					if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_DATACENTER)
						strWindowsVersion += " DataCenter Server ";
					else if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_ENTERPRISE)
						strWindowsVersion += " Advanced Server ";
					else
						strWindowsVersion += " Server ";
				}
				break;
			case 1:
				IsWinXP=true;
				strWindowsVersion = "Windows XP";
				if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_PERSONAL)
					strWindowsVersion += " Home Edition";
				else
					strWindowsVersion += " Professionel";
				break;
			case 2:
				if(GetSystemMetrics(SM_SERVERR2)!=0)
				{
					IsWin2003=true;
					if(OSinfo.wProductType==VER_SUITE_STORAGE_SERVER)
						strWindowsVersion = "Windows Storage Server 2003 R2";
					else
						strWindowsVersion = "Windows Server 2003 R2";
				}
				else if(OSinfo.wProductType==VER_SUITE_WH_SERVER)
				{
					IsWinHomeServer=true;
					strWindowsVersion = "Windows Home Server";
				}
				else if(OSinfo.wProductType==VER_SUITE_STORAGE_SERVER)
				{
					IsWin2003=true;
					strWindowsVersion = "Windows Storage Server 2003";
				}
				else if(OSinfo.wProductType==VER_NT_WORKSTATION&&IsWin64bit)
				{
					IsWinXP=true;
					strWindowsVersion = "Microsoft Windows XP Professional x64 Edition";
				}
				else
				{
					IsWin2003=true;
					strWindowsVersion="Windows Server 2003";
				}
				if(OSinfo.wProductType!=VER_NT_WORKSTATION)
				{
					GetNativeSystemInfo(&SysInfo);
					if(SysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
					{
						if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_DATACENTER)
							strWindowsVersion += " Datacenter Edition pour Itanium";
						else if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_ENTERPRISE)
							strWindowsVersion += " Enterprise Edition pour Itanium";
					}
					else if(SysInfo.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
					{
						if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_DATACENTER)
							strWindowsVersion += " Datacenter x64 Edition";
						else if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_ENTERPRISE)
							strWindowsVersion += " Enterprise x64 Edition";
						else
							strWindowsVersion += " Standard x64 Edition";
					}
					else
					{
						if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_DATACENTER)
							strWindowsVersion += " Datacenter Edition";
						else if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_ENTERPRISE)
							strWindowsVersion += " Enterprise Edition";
						else if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_COMPUTE_SERVER)
							strWindowsVersion += " Compute Cluster Edition";
						else if(OSinfo.wSuiteMask&&OSinfo.wSuiteMask==VER_SUITE_BLADE)
							strWindowsVersion += " Web Edition";
						else
							strWindowsVersion += " Standard Edition";
					}
				}
				break;
			default:
				char temp[10];
				strWindowsVersion="Windows NT v";
				_itoa_s(OSinfo.dwMajorVersion,temp,sizeof(temp),10);
				strWindowsVersion.append(temp);
				strWindowsVersion.append(".");
				_itoa_s(OSinfo.dwMinorVersion,temp,sizeof(temp),10);
				strWindowsVersion.append(temp);
				//strWindowsVersion.append("Windows NT v%d.%d",OSinfo.dwMajorVersion,OSinfo.dwMinorVersion);
				break;

			}
			strWindowsVersion.append(InfoVersion64bit());
			//			strWindowsVersion.append(InfoVersionMediaCenter());

			break;
		default:
			char temp[10];
			strWindowsVersion="Windows NT v";
			_itoa_s(OSinfo.dwMajorVersion,temp,sizeof(temp),10);
			strWindowsVersion.append(temp);
			strWindowsVersion.append(".");
			_itoa_s(OSinfo.dwMinorVersion,temp,sizeof(temp),10);
			strWindowsVersion.append(temp);
			strWindowsVersion.append(".");
			_itoa_s(OSinfo.dwBuildNumber,temp,sizeof(temp),10);
			strWindowsVersion.append(temp);
			if(OSinfo.dwMajorVersion==4&&OSinfo.wProductType==VER_NT_WORKSTATION)
				strWindowsVersion += " Workstation";
			break;
		}
		if(OSinfo.wServicePackMajor>0)
		{
			char temp[10];
			strWindowsVersion.append(" Service Pack ");
			_itoa_s(OSinfo.wServicePackMajor,temp,sizeof(temp),10);
			strWindowsVersion.append(temp);
			if(OSinfo.wServicePackMinor>0)
			{
				_itoa_s(OSinfo.wServicePackMinor,temp,sizeof(temp),10);
				strWindowsVersion.append(temp);
			}
		}
	}
	return strWindowsVersion;
}

string InfoVersionWin()
{
	string strWindowsVersion="";
    OSVERSIONINFO OSinfo;
    long RetValue;
    string strPssInfo;
    OSinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    RetValue = GetVersionEx(&OSinfo);
    if(1)
    {
        OSinfo.dwBuildNumber=LOWORD(OSinfo.dwBuildNumber);
        switch(OSinfo.dwPlatformId)
        {
        case VER_PLATFORM_WIN32_WINDOWS:
            IsWin9x=true;
            switch(OSinfo.dwMinorVersion)
            {
            case 0:
                IsWin95=true;
                switch(OSinfo.dwBuildNumber)
                {
                case 950:
                    strWindowsVersion = "Windows 95";
                    break;
                case 111:
                    strWindowsVersion = "Windows 95 SR2.5";
                    break;
                default:
                    strWindowsVersion = "Windows 95 SR2";
                    break;
                }
                break;
            case 3:
                IsWin95=true;
                strWindowsVersion = "Windows 95 SR2.x";
                break;
            case 10:
                if(OSinfo.dwBuildNumber==2222)
                {
                    IsWin98SE=true;
                    strWindowsVersion = "Windows 98 Second Edition";
                }
                else
                {
                    IsWin98=true;
                    strWindowsVersion = "Windows 98";
                }
                break;
            case 90:
                IsWin98ME=true;
                strWindowsVersion="Windows Me (Millenium)";
                break;
            default:
                char temp[10];
                strWindowsVersion = "Windows v";
                _itoa_s(OSinfo.dwMajorVersion,temp,sizeof(temp),10);
                strWindowsVersion.append(temp);
                strWindowsVersion.append(".");
                _itoa_s(OSinfo.dwMinorVersion,temp,sizeof(temp),10);
                strWindowsVersion.append(temp);
                strWindowsVersion.append(".");
                _itoa_s(OSinfo.dwBuildNumber,temp,sizeof(temp),10);
                strWindowsVersion.append(temp);
                break;
            }
            break;
        case VER_PLATFORM_WIN32_NT:
            IsWinNT=true;
            switch(OSinfo.dwMajorVersion)
            {
            case 3:
                IsWinNT3=true;
                switch(OSinfo.dwMinorVersion)
                {
                case 0:
                    strWindowsVersion = "Windows NT 3";
                    break;
                case 1:
                    strWindowsVersion = "Windows NT 3.1";
                    break;
                case 51:
                    strWindowsVersion = "Windows NT 3.51";
                    break;
                default:
                    strWindowsVersion = "Windows NT";
                    break;
                }
                break;
            case 4:
                IsWinNT4=true;
                strWindowsVersion = "Windows NT 4.0";
                break;
            case 5:
                break;
            default:
                char temp[20];
                strWindowsVersion = "Windows NT v";
                _itoa_s(OSinfo.dwMajorVersion,temp,sizeof(temp),10);
                strWindowsVersion.append(temp);
                strWindowsVersion.append(".");
                _itoa_s(OSinfo.dwMinorVersion,temp,sizeof(temp),10);
                strWindowsVersion.append(temp);
                strWindowsVersion.append(".");
                _itoa_s(OSinfo.dwBuildNumber,temp,sizeof(temp),10);
                strWindowsVersion.append(temp);
                break;
            }
            break;
        case VER_PLATFORM_WIN32s:
            IsWin32s=true;
            strWindowsVersion="Win32s";
            break;
        case 3:
            break;
        default:
            strWindowsVersion="ERROE";
            break;
        }
        /*
        strPassInfo=OSinfo.szCSDVersion;
        if(sizeof(strPassInfo)>0)
        {
            if(
        }
        */
    }
    return strWindowsVersion;
	
}

string InfoVersion64bit()
{
	SYSTEM_INFO Si;
	string strTemp;
	GetNativeSystemInfo(&Si);
	if(Si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
	{
		strTemp=" 64bits";
		IsWin64bit=true;
	}
	else
	{
		strTemp=" 32bits";
		IsWin64bit=false;
	}
	return strTemp;
}

string GetDllVersion()
{
	TCHAR szFullPath[MAX_PATH];
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO * pFileInfo;

	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
	dwVerInfoSize = GetFileVersionInfoSize((LPCWSTR)"LoggerCore.dll", &dwVerHnd);
	int error = GetLastError();
	if (dwVerInfoSize)
	{
		// If we were able to get the information, process it:
		HANDLE  hMem;
		LPVOID  lpvMem;
		unsigned int uInfoSize = 0;

		hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);

		::VerQueryValue(lpvMem, (LPTSTR)"\\", (void**)&pFileInfo, &uInfoSize);

		int ret = GetLastError();
		WORD m_nProdVersion[4];

		// Product version from the FILEVERSION of the version info resource 
		m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
		m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
		m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
		m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 

		
		char ver[256];
		memset(ver,0,sizeof(ver));
		sprintf(ver,"%d.%d.%d.%d",m_nProdVersion[0],
			m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
		string strVersion(ver);
		GlobalUnlock(hMem);
		GlobalFree(hMem);
		return strVersion;
	}
	return "";
}