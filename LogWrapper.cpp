#ifdef WIN32
//#include "StdAfx.h"
#else
#include <dlfcn.h>
#endif
#include "LogWrapper.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>

typedef void (*FN_Init)();
typedef void (*FN_UnInit)();
typedef std::string (*FN_Open)(const char *log);
typedef bool (*FN_Close)(std::string h);
typedef bool (*FN_MLogWrite)(int type, std::string h, const char *log, unsigned short logLen);
typedef bool (*FN_MLogWriteHex)(int type, std::string h, const char *prefix, const char *data, unsigned short dataLen);

static HMODULE s_hModule = NULL;
static FN_Init s_init = NULL;
static FN_UnInit s_uninit = NULL;
static FN_Open s_open = NULL;
static FN_Close s_close = NULL;
static FN_MLogWrite s_write = NULL;
static FN_MLogWriteHex s_writeHex = NULL;

LogWrapper::LogWrapper(void)
{
	m_hLog = "";
}

LogWrapper::~LogWrapper(void)
{
}

void LogWrapper::Open( const char *name )
{
    if(s_open != NULL)
        m_hLog = s_open(name);
}

void LogWrapper::Close()
{
    if(s_close != NULL)
        s_close(m_hLog);
}

bool LogWrapper::Write(int type,  const char *format, ... )
{
    va_list args;
    va_start(args, format);
    memset(m_buf, 0, MAX_BUF_SIZE);
    vsprintf(m_buf, format, args);
    m_buf[MAX_BUF_SIZE - 1] = '\0';
    va_end(args);

    if(s_write != NULL)
        return	s_write(type, m_hLog, m_buf, strlen(m_buf));
    return false;
}

bool LogWrapper::WriteHex(int type,  const char *data, unsigned short dataLen, const char *format, ... )
{
    va_list args;
    memset(m_buf, 0, MAX_BUF_SIZE);
    va_start(args, format);
    vsprintf(m_buf, format, args);
    m_buf[MAX_BUF_SIZE - 1] = '\0';
    va_end(args);

    if(s_writeHex != NULL)
        return s_writeHex(type, m_hLog, m_buf, data, dataLen);
    return false;
}

//bool LogWrapper::writeDebug(const char *format, ...)
//{
//	va_list args;
//	va_start(args, format);
//	memset(m_buf, 0, MAX_BUF_SIZE);
//	vsprintf(m_buf, format, args);
//	m_buf[MAX_BUF_SIZE - 1] = '\0';
//	va_end(args);
//
//	if (s_write != NULL)
//		return	s_write(LogWrapper::LOG_LEVEL_DEBUG, m_hLog, m_buf, strlen(m_buf));
//	return false;
//}
//
//bool LogWrapper::writeInfo(const char *format, ...)
//{
//	va_list args;
//	va_start(args, format);
//	memset(m_buf, 0, MAX_BUF_SIZE);
//	vsprintf(m_buf, format, args);
//	m_buf[MAX_BUF_SIZE - 1] = '\0';
//	va_end(args);
//
//	if (s_write != NULL)
//		return	s_write(LogWrapper::LOG_LEVEL_INFO, m_hLog, m_buf, strlen(m_buf));
//	return false;
//}

void LogWrapper::Load()
{
	if(s_hModule != NULL)
		return;
#ifdef WIN32
	char lpszPath[1024];
	Utility::GetCurrentDir(lpszPath, 1024);
	strcat(lpszPath, "PLog.dll");
	s_hModule = ::LoadLibraryA(lpszPath);
	if(!s_hModule)
		return;
	s_init =(FN_Init)::GetProcAddress(s_hModule, "MLogInit");
	s_uninit =(FN_UnInit)::GetProcAddress(s_hModule, "MLogUnInit");
	s_open =(FN_Open)::GetProcAddress(s_hModule, "MLogOpen");
	s_close = (FN_Close)::GetProcAddress(s_hModule, "MLogClose");
	s_write = (FN_MLogWrite)::GetProcAddress(s_hModule, "MLogWrite");
	s_writeHex = (FN_MLogWriteHex)::GetProcAddress(s_hModule, "MLogWriteHex");
#else
	s_hModule = dlopen("./libplog.so", RTLD_NOW);
	if (s_hModule)
	{
		printf("dlopen libplog.so successed\n");
		s_init =(FN_Init)dlsym(s_hModule, "PLogInit");
		s_uninit =(FN_UnInit)dlsym(s_hModule, "PLogUnInit");
		s_open =(FN_Open)dlsym(s_hModule, "PLogOpen");
		s_close = (FN_Close)dlsym(s_hModule, "PLogClose");
		s_write = (FN_MLogWrite)dlsym(s_hModule, "PLogWrite");
		s_writeHex = (FN_MLogWriteHex)dlsym(s_hModule, "PLogWriteHex");
	}
	else
		printf("dlopen libplog.so failed\n");
#endif
	if(s_init != NULL)
		s_init();
}

void LogWrapper::Free()
{
	if(s_uninit != NULL)
	{
		s_uninit();
		s_uninit = NULL;
	}
	if(s_hModule == NULL)
		return;
#ifdef WIN32
	::FreeLibrary(s_hModule);
#else
	dlclose(s_hModule);
#endif
	s_hModule = NULL;
	s_init = NULL;
	s_uninit = NULL;
	s_open = NULL;
	s_close = NULL;
	s_write = NULL;
	s_writeHex = NULL;
}


#ifndef WIN32
bool LogWrapper::WriteDebug(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	memset(m_buf, 0, MAX_BUF_SIZE);
	vsprintf(m_buf, format, args);
	m_buf[MAX_BUF_SIZE - 1] = '\0';
	va_end(args);

	if (s_write != NULL)
		return	s_write(LogWrapper::LOG_LEVEL_DEBUG, m_hLog, m_buf, strlen(m_buf));
	return false;
}

bool LogWrapper::WriteInfo(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	memset(m_buf, 0, MAX_BUF_SIZE);
	vsprintf(m_buf, format, args);
	m_buf[MAX_BUF_SIZE - 1] = '\0';
	va_end(args);

	if (s_write != NULL)
		return	s_write(LogWrapper::LOG_LEVEL_INFO, m_hLog, m_buf, strlen(m_buf));
	return false;
}

bool LogWrapper::WriteError(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	memset(m_buf, 0, MAX_BUF_SIZE);
	vsprintf(m_buf, format, args);
	m_buf[MAX_BUF_SIZE - 1] = '\0';
	va_end(args);

	if (s_write != NULL)
		return	s_write(LogWrapper::LOG_LEVEL_ERROR, m_hLog, m_buf, strlen(m_buf));
	return false;

}

bool LogWrapper::WriteFatal(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	memset(m_buf, 0, MAX_BUF_SIZE);
	vsprintf(m_buf, format, args);
	m_buf[MAX_BUF_SIZE - 1] = '\0';
	va_end(args);

	if (s_write != NULL)
		return	s_write(LogWrapper::LOG_LEVEL_FATAL, m_hLog, m_buf, strlen(m_buf));
	return false;
}

#endif // !WIN32

