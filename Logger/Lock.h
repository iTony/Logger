#pragma once
class Lock
{
public:
	Lock(HANDLE mutex);
	void UnLock();
	~Lock(void);
private:
	HANDLE m_mutex;
};

