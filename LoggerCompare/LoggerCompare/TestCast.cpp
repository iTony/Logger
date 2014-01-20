#include "StdAfx.h"
#include "TestCast.h"
#include <fstream>
#include <io.h>
#include "LogMsg.h"

using namespace std;

TestCase::TestCase(void)
{
	rightCount = 0;
	wrongCount = 0;
	ExceptionCount = 0;
	numd = 0;
	posd = 0;
	filepath = new char[MAX_PATH];
	memset(filepath,0,MAX_PATH);
	xmlPath = "";
	htmlPath = "";

}

TestCase::~TestCase(void)
{
	vector<LogMsg*>::iterator it;
	for (it=recordList.begin();it!=recordList.end();it++)
	{
		delete *it;
		//recordList.erase(it);
	}
	recordList.clear();
	for (it=playbackList.begin();it!=playbackList.end();it++)
	{
		delete *it;
		
	}
	playbackList.clear();
}

void TestCase::GetRecordLog(char* path)
{
	char buffer[512];
	memset(buffer,0,sizeof(buffer));
	ifstream  fin;
	fin.open(path);
	fin.getline(buffer,sizeof(buffer));
	fin.getline(buffer,sizeof(buffer));
	while(!fin.eof()){
		LogMsg *msg = GetLogMsg(buffer);
		recordList.push_back(msg);
		memset(buffer,0,sizeof(buffer));
		fin.getline(buffer,sizeof(buffer));
	}
	RecordSort();
}

void TestCase::GetPlaybackLog(char* path)
{
	char* pos = path;
	int t = 0;
	//char temp[MAX_PATH];
	//memset(temp,0,strlen(temp));
	int len = strlen(path);
	
	for (int i=0;i<len;i++)
	{
		if (pos[i]=='%')
		{
			i++;
			int pd = t;
			int count = 0;
			char tmp[10];
			memset(tmp,0,10);
			int n =0;
			while(pos[i]>='0'&&pos[i]<='9')
			{
				filepath[t] = pos[i];
				tmp[n] = pos[i];
				i++;
				t++;
				count++;
			}
			if (pos[i]=='t')
			{
				int j = 14-count;
				for (int j=0;j<14-count;j++)
				{
					filepath[t] = '%';
					t++;
				}
			}
			else if(pos[i]=='d')
			{
				if (count == 0)
				{
					filepath[t] = '0';
					t++;
					numd = 1;
				}
				else
				{
					numd = count;
				}
				cnum = atoi(tmp);
				
				posd = pd;
			}
		}
		else
		{
			filepath[t] = pos[i];
			t++;
		}
	}
	filepath[t] = '\0';
}

void TestCase::ClearPlaybackLog()
{
	vector<LogMsg*>::iterator it;
	for (it=playbackList.begin();it!=playbackList.end();it++)
	{
		delete *it;

	}
	playbackList.clear();
}

void TestCase::GetPlaybackFile(char* path)
{
	ClearPlaybackLog();
	char buffer[512];
	memset(buffer,0,sizeof(buffer));
	ifstream  fin;
	fin.open(path);
	fin.getline(buffer,sizeof(buffer));
	fin.getline(buffer,sizeof(buffer));
	while(!fin.eof()){
		LogMsg *msg = GetLogMsg(buffer);
		playbackList.push_back(msg);
		memset(buffer,0,sizeof(buffer));
		fin.getline(buffer,sizeof(buffer));
	}

	PlaybackSort();
}

LogMsg* TestCase::GetLogMsg(char* buffer)
{
	
	char time[24];
	memset(time,'\0',sizeof(time));
	char level[6];
	memset(level,'\0',sizeof(level));
	char thread[50];
	memset(thread,'\0',sizeof(thread));
	char clsName[50];
	memset(clsName,'\0',sizeof(clsName));
	char funName[50];
	memset(funName,'\0',sizeof(funName));
	char message[512];
	memset(message,'\0',sizeof(message));

	char *pbuf = buffer+sizeof(time);
	memcpy(time,buffer,sizeof(time)-1);
	time[23]='\0';
	int i=0;
	while(*pbuf!=' ')
	{
		level[i] = *pbuf;
		i++;
// 		level++;
 		pbuf++;
	}

	pbuf++;
	pbuf++;
	i=0;
	while(*pbuf!=']')
	{
		thread[i] = *pbuf;
		i++;
		pbuf++;
	}

	pbuf++;
	pbuf++;
	i=0;
	while(*pbuf!='(')
	{
		clsName[i] = *pbuf;
		i++;
		pbuf++;
	}
	pbuf++;
	i=0;
	while(*pbuf!=','&&*pbuf!=')')
	{
		funName[i] = *pbuf;
		i++;
		pbuf++;
	}

	while(*pbuf!=' ')
	{
		pbuf++;
	}

	pbuf++;

	strcpy(message,pbuf);
	//int size = sizeof(time);
	LogMsg* msg = new LogMsg(time,level,clsName,funName,thread,message);
	return msg;
}

void TestCase::RecordSort()
{
	string tname = "";
	for (int i=0;i<recordList.size()-1;i++)
	{
		//LogMsg* tmpL = recordList[i];
		string thread = recordList[i]->GetThread();
		if (thread!=tname)
		{
			threadName.push_back(thread);
			tname = thread;
		}
		int t=i+1;
		string thread1 = recordList[t]->GetThread();
		if (thread1 == thread)
		{
			continue;
		}
		
		int j=t;
		for (j++;j<recordList.size();j++)
		{

			string trd = recordList[j]->GetThread();
			if (thread==trd)
			{
				for (int a=j;a>t;a--)
				{
					LogMsg* log = recordList[a];
					recordList[a] = recordList[a-1];
					recordList[a-1] = log;
				}
				t++;
				i++;
			}
		}
	}
}

void TestCase::PlaybackSort()
{
	int num = 0;
	for (int n=0;n<threadName.size();n++)
	{
		string name = threadName[n];
		int cur = num;
		for (;cur<playbackList.size();cur++)
		{
			if (playbackList[cur]->GetThread()==name)
			{
				for (int i=cur;i>num;i--)
				{
					LogMsg *log = playbackList[i];
					playbackList[i] = playbackList[i-1];
					playbackList[i-1] = log;
				}
				num++;
			}
		}
	}
}

void TestCase::ClearTestReport()
{
	vector<TestReport*>::iterator it;
	for (it=reportList.begin();it!=reportList.end();it++)
	{
		delete *it;

	}
	reportList.clear();
}

void TestCase::CreateTestReport()
{
	rightCount = 0;
	wrongCount = 0;
	ExceptionCount = 0;
	ClearTestReport();
	int flag = 0;
	if (recordList.size()>playbackList.size())
	{
		flag = 1;
	}
	if (recordList.size()<playbackList.size())
	{
		flag = 2;
	}
	for (int i=0,j=0;i<recordList.size();i++,j++)
	{
		LogMsg* record = recordList[i];
		LogMsg* playback = playbackList[j];
		string clsName = record->GetClsName();
		string funName = record->GetFunName();
		string level = record->GetLevel();
		string thread = record->GetThread();
		string info = clsName+"_"+funName+"_"+thread;
		string message = record->GetMessage();
		string result = "";
		if (clsName==playback->GetClsName()&&
			funName==playback->GetFunName()&&
			level==playback->GetLevel()&&
			thread == playback->GetThread())
		{
			if (message == playback->GetMessage())
			{
				result = "Right";
				rightCount++;
			}
			else
			{
				result = "Wrong";
				wrongCount++;
			}
			//TestReport* report = new TestReport(level,info,message,playback->GetMessage(),result);
			TestReport* report = new TestReport(level,clsName,funName,thread,message,playback->GetMessage(),result);
			reportList.push_back(report);
		}
		else
		{
			result = "Exception";
			ExceptionCount++;
			if (flag == 2)
			{
				TestReport* report = new TestReport("NULL","NULL","NULL","NULL","NULL",playback->GetMessage(),result);
				reportList.push_back(report);
				j++;
			}
			else if(flag == 1)
			{
				TestReport* report = new TestReport(level,clsName,funName,thread,message,"NULL",result);
				reportList.push_back(report);
				i++;
			}
			else
			{
				TestReport* report = new TestReport(level,clsName,funName,thread,message,playback->GetMessage(),result);
				reportList.push_back(report);
			}
		}
	}
}

void TestCase::Compare()
{
	int len = strlen(filepath)-1;

	for (;len>=0;len--)
	{
		if (filepath[len] == '\\')
		{
			break;
		}
	}
	posd = posd - len-1;
	TCHAR szFind[100] ;
	memset(szFind,0,100);

	MultiByteToWideChar(CP_OEMCP,0,filepath,-1,szFind,len+1);
	szFind[len+1] = '*';
	char *file = filepath+len+1;
	WIN32_FIND_DATA fdata = {0};
	HANDLE hFind = FindFirstFile(szFind,&fdata);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do 
	{
		if (fdata.cFileName[0] == '.')
		{
			continue;
		}
		if (fdata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}
		else
		{
			//TCHAR* szFile = fdata.cFileName;
			char szFile[100];
			memset(szFile,0,100);
			WideCharToMultiByte(CP_OEMCP,NULL,fdata.cFileName,-1,szFile,sizeof(fdata.cFileName),NULL,FALSE);
			int size = strlen(szFile);
			bool flag = true;

			for (int i=0,m=0;i<size;i++,m++)
			{
				if (i == posd)
				{
					char tmp[10];
					memset(tmp,0,sizeof(tmp));
					int n = 0;
					for (;i<size;i++)
					{
						if (file[i]==szFile[m+numd])
						{
							int cn = atoi(tmp);
							if (cn<cnum)
							{
								flag = false;
								break;
							}
							break;
						}
						if (file[i]<'0'||file[i]>'9')
						{
							flag = false;
							break;
						}
						tmp[n] = file[i];
						n++;
						//m++;
					}
					if (i==size)
					{
						int cn = atoi(tmp);
						if (cn<cnum)
						{
							flag = false;
							break;
						}
						
					}
					m+=numd;
					m--;
					i--;
				}
				else if (file[i]!=szFile[m]&&'%'!= file[i])
				{
					flag = false;
					break;
				}
				
			}
			if (flag)
			{
				int szlen = strlen(szFile);
				int szflag = 0;
				int llen = len+1;
				char tpath[MAX_PATH];
				memset(tpath,0,MAX_PATH);
				memcpy(tpath,filepath,strlen(filepath));
				for (int i=0;i<szlen;i++)
				{
					tpath[llen+i]=szFile[i];
					if (szFile[i] == '.')
					{
						szflag = i;
					}
				}
				tpath[llen+szlen] = '\0';
				szFile[szflag+1] = '\0';
				GetPlaybackFile(tpath);
				CreateTestReport();
				if (xmlPath!="")
				{
					string xml = xmlPath;
					xml.append("\\");
					xml.append(szFile);
					xml.append("xml");
					CreateReportXML((char *)xml.c_str());
				}
				if (htmlPath!="")
				{
					string html = htmlPath;
					html.append("\\");
					html.append(szFile);
					html.append("html");
					CreateReportHTML((char *)html.c_str());
				}
			}

		}

	} while (FindNextFile(hFind,&fdata));
	FindClose(hFind);
}

void TestCase::CreateReportXML(char* path)
{
	ofstream fout;
	fout.open(path);
	char num[16];
	memset(num,0,sizeof(num));
	string log = "<TestReport>\n";
	int sum = rightCount+wrongCount+ExceptionCount;
	log.append("	<Total>");
	itoa(sum,num,10);
	log.append(num);
	log.append("</Total>\n");
	log.append("	<Right>");
	memset(num,0,sizeof(num));
	itoa(rightCount,num,10);
	log.append(num);
	log.append("</Right>\n") ;
	log.append("	<Wrong>");
	memset(num,0,sizeof(num));
	itoa(wrongCount,num,10);
	log.append(num);
	log.append("</Wrong>\n") ;
	log.append("	<Exception>");
	memset(num,0,sizeof(num));
	itoa(ExceptionCount,num,10);
	log.append(num);
	log.append("</Exception>\n") ;
	log.append("</TestReport>\n") ;
	
	for (int i=0;i<reportList.size();i++)
	{
		log.append("<TestReport>\n") ;
		log.append("	<Level>");
		log.append(reportList[i]->GetLevel());
		log.append("</Level>\n") ;
		log.append("	<ClassName>");
		log.append(reportList[i]->GetClassName());
		log.append("</ClassName>\n");
		log.append("	<FunName>");
		log.append(reportList[i]->GetFunName());
		log.append("</FunName>\n");
		log.append("	<Thread>");
		log.append(reportList[i]->GetThread());
		log.append("</Thread>\n");
		log.append("	<RecordMessage>");
		log.append(reportList[i]->GetRecordMsg());
		log.append("</RecordMessage>\n") ;
		log.append("	<PlaybackMessage>");
		log.append(reportList[i]->GetPlaybackMsg());
		log.append("</PlaybackMessage>\n") ;
		log.append("	<Result>");
		log.append(reportList[i]->GetTestResult());
		log.append("</Result>\n") ;
		log.append("</TestReport>\n") ;
	}

	fout<<log;
	fout.flush();
	fout.close();
}

void TestCase::CreateReportHTML(char* path)
{
	ofstream fout;
	fout.open(path);
	char num[16];
	memset(num,0,sizeof(num));
	string log = "<tr>\n\t<td>Level</td>\n\t<td>ClassName</td>\n\t<td>FunName</td>\n\t<td>Thread</td>\n\t<td>RecordMessage</td>\n\t<td>PlaybackMessage</td>\n\t<td>Result</td>\n</tr>\n";
	for (int i=0;i<reportList.size();i++)
	{
		log.append("<tr>\n") ;
		log.append("	<td>");
		log.append(reportList[i]->GetLevel());
		log.append("</td>\n") ;
		log.append("	<td>");
		log.append(reportList[i]->GetClassName());
		log.append("</td>\n");
		log.append("	<td>");
		log.append(reportList[i]->GetFunName());
		log.append("</td>\n");
		log.append("	<td>");
		log.append(reportList[i]->GetThread());
		log.append("</td>\n");
		log.append("	<td>");
		log.append(reportList[i]->GetRecordMsg());
		log.append("</td>\n") ;
		log.append("	<td>");
		log.append(reportList[i]->GetPlaybackMsg());
		log.append("</td>\n") ;
		log.append("	<td>");
		log.append(reportList[i]->GetTestResult());
		log.append("</td>\n") ;
		log.append("</tr>\n") ;
	}
	int sum = rightCount+wrongCount+ExceptionCount;
	log.append("<tr>\n\t<td>");
	itoa(sum,num,10);
	log.append(num);
	log.append("</td>\n");
	log.append("	<td>");
	memset(num,0,sizeof(num));
	itoa(rightCount,num,10);
	log.append(num);
	log.append("</td>\n") ;
	log.append("	<td>");
	memset(num,0,sizeof(num));
	itoa(wrongCount,num,10);
	log.append(num);
	log.append("</td>\n") ;
	log.append("	<td>");
	memset(num,0,sizeof(num));
	itoa(ExceptionCount,num,10);
	log.append(num);
	log.append("</td>\n") ;
	log.append("</tr>\n") ;

	fout<<log;
	fout.flush();
	fout.close();
}