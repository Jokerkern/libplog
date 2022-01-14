#pragma once
#include <iostream>
#include <memory>
#include <cstring>
#include <list>
#include <sys/types.h>
#include <stddef.h>
#include <vector>
#include <thread>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // support for user defined types
#include "spdlog/sinks/rotating_file_sink.h"
#include "httpServer.h"
#include "webSocketControl.h"
#include "AutoLock.h"
#include "tcp_sink.h"
#include "websocket_sink.h"
#include "PLogConfig.h"
typedef void * HANDLE;
class PLogControl
{
private:
    Lock pLock;
    std::list<spdlog::logger *> loggerList;
    bool loggerIsValid(spdlog::logger *logger);
public:
	PLogControl();
	~PLogControl();
    static std::shared_ptr<webSocketControl> g;
    enum
    {
        LOG_LEVEL_FATAL = 0,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG,
    };

    static void* webServer(void* data);
    static void* webSocket(void* data);
    static void* logFlush(void* data);

    bool StartThread();
    bool StopThread();

    HANDLE PLogOpen(const char *log);
    bool PLogClose(HANDLE h);
	bool PLogWrite(int type, HANDLE h, const char *log, unsigned short logLen);
    bool PLogWriteHex(int type, HANDLE h, const char *prefix, const char *data, unsigned short dataLen);

};
