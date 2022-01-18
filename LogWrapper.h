#pragma once
#include <string>
#ifdef WIN32
#include <Windows.h>
#else
#define HMODULE void*
#endif
#pragma execution_character_set("utf-8")


enum
{
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DEBUG,
};

#ifdef WIN32
// �Զ������ļ����ơ��кźͺ�������
#define WriteEx(type, lpszFormat, ...)\
	Write(type, "<(line:%d)  %s> ^ "lpszFormat, __LINE__, __FUNCTION__, ##__VA_ARGS__);
#define WriteDebug( lpszFormat, ...)\
	Write(LogWrapper::LOG_LEVEL_DEBUG, "<(line:%d)  %s> ^ "lpszFormat, __LINE__, __FUNCTION__, ##__VA_ARGS__);
#define WriteInfo( lpszFormat, ...)\
	Write(LogWrapper::LOG_LEVEL_INFO, "<(line:%d)  %s> ^ "lpszFormat, __LINE__, __FUNCTION__, ##__VA_ARGS__);
#define WriteError( lpszFormat, ...)\
	Write(LogWrapper::LOG_LEVEL_ERROR, "<(line:%d)  %s> ^ "lpszFormat, __LINE__, __FUNCTION__, ##__VA_ARGS__);
#define WriteFatal( lpszFormat, ...)\
	Write(LogWrapper::LOG_LEVEL_FATAL, "<(line:%d)  %s> ^ "lpszFormat, __LINE__, __FUNCTION__, ##__VA_ARGS__);
#endif

class LogWrapper
{
public:
	LogWrapper(void);
	~LogWrapper(void);

	enum
	{
		LOG_LEVEL_FATAL = 0,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_INFO,
		LOG_LEVEL_DEBUG,
	};


public:
    void Open(const char *name);
    void Close();
    bool Write(int type, const char *format, ...);
    bool WriteHex(int type, const char *data, unsigned short dataLen, const char *format, ...);

#ifndef WIN32
	bool WriteDebug(const char *format, ...);
	bool WriteInfo(const char *format, ...);
	bool WriteError(const char *format, ...);
	bool WriteFatal(const char *format, ...);
#endif // !WIN32

public:
	static void Load();
	static void Free();

private:
	std::string m_hLog;
	static const int MAX_BUF_SIZE = 1024 * 5;
	char m_buf[MAX_BUF_SIZE];
};


