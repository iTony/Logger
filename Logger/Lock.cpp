#include "StdAfx.h"
#include "Lock.h"
#include <Windows.h>

Lock::Lock(HANDLE mutex):m_mutex(mutex)
{
	m_mutex = ::CreateMutex(NULL, FALSE, NULL);
	WaitForSingleObject(m_mutex,INFINITE);
}

Lock::~Lock(void)
{
}

void Lock::UnLock()
{
	ReleaseMutex(m_mutex);
}
