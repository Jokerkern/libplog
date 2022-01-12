#ifndef __PLOG_H__
#define __PLOG_H__
#ifdef WIN32
#ifdef PLOG_EXPORTS
#define PLOG_API __declspec(dllexport)
#else
#define PLOG_API __declspec(dllimport)
#endif
#else
#define PLOG_API extern
typedef void *HANDLE;
#endif

#ifdef __cplusplus
extern "C" {
#endif
    PLOG_API void PLogInit();
    PLOG_API void PLogUnInit();
    PLOG_API HANDLE PLogOpen(const char *log);
    PLOG_API bool PLogClose(HANDLE h);
    PLOG_API bool PLogWrite(int type, HANDLE h, const char *log, unsigned short logLen);
    PLOG_API bool PLogWriteHex(int type, HANDLE h, const char *prefix, const char *data, unsigned short dataLen);
#ifdef __cplusplus
};
#endif

#endif
