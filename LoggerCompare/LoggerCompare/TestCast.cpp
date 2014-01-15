#include "StdAfx.h"
#include "TestCast.h"
#include <fstream>
#include "LogMsg.h"

using namespace std;

TestCase::TestCase(void)
{
	rightCount = 0;
	wrongCount = 0;
	ExceptionCount = 0;
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
	memcpy(time,buffer,sizeof(time));

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
	int size = sizeof(time);
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
		string thread1 = recordList[i+1]->GetThread();
		if (thread1 == thread)
		{
			continue;
		}
		int t=i+1;
		int j=t;
		for (j++;j<recordList.size();j++)
		{

			string trd = recordList[j]->GetThread();
			if (thread==trd)
			{
				LogMsg* log = recordList[j];
				recordList[j] = recordList[t];
				recordList[t] = log;
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
				if (num!=cur)
				{
					LogMsg *log = playbackList[num];
					playbackList[num] = playbackList[cur];
					playbackList[cur] = log;
				}
				num++;
			}
		}
	}
}

void TestCase::Compare()
{
	bool flag = true;
	if (recordList.size()>playbackList.size())
	{
		flag = false;
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
			if (flag)
			{
				TestReport* report = new TestReport("NULL","NULL","NULL","NULL","NULL",playback->GetMessage(),result);
				reportList.push_back(report);
				j++;
			}
			else
			{
				TestReport* report = new TestReport(level,clsName,funName,thread,message,"NULL",result);
				reportList.push_back(report);
				i++;
			}
		}
	}
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