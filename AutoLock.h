#pragma once
#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

class Lock
{
public:
	Lock()
	{
#ifdef WIN32
		::InitializeCriticalSection(&m_csLock); 
#else
		pthread_mutex_init(&m_mutex, NULL);
#endif
	}
	~Lock()
	{
#ifdef WIN32
		::DeleteCriticalSection(&m_csLock);
#else
		pthread_mutex_destroy(&m_mutex);
#endif
	}

	void LockBegin()
	{
#ifdef WIN32
		::EnterCriticalSection(&m_csLock);
#else
		pthread_mutex_lock(&m_mutex);
#endif
	}

	void LockEnd()
	{
#ifdef WIN32
		::LeaveCriticalSection(&m_csLock);
#else
		pthread_mutex_unlock(&m_mutex);
#endif
	}
private:
#ifdef WIN32
	CRITICAL_SECTION m_csLock;
#else
	pthread_mutex_t m_mutex;
#endif
};

class AutoLock
{
	private:
		Lock *m_lock;
public:
	AutoLock(Lock & lock)
		:m_lock(&lock)
	{
		m_lock->LockBegin();
	}
	~AutoLock(void)
	{
		m_lock->LockEnd();
	}
};
