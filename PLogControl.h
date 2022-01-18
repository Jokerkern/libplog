#pragma once
#include <iostream>
#include <memory>
#include <cstring>
#include <unordered_map>
#include <sys/types.h>
#include <stddef.h>
#include <vector>
#include <thread>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // support for user defined types
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "httpServer.h"
#include "webSocketControl.h"
#include "AutoLock.h"
#include "tcp_sink.h"
#include "websocket_sink.h"
#include "PLogConfig.h"
class PLogControl
{
private:
    Lock pLock;
    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> loggerMap;
    bool loggerIsValid(std::shared_ptr<spdlog::logger>);
public:
	PLogControl();
	~PLogControl();
    enum
    {
        LOG_LEVEL_FATAL = 0,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG,
    };

    static void webServer();
    static void webSocket();
    static void* logFlush(void* data);

    bool StartThread();
    bool StopThread();

    std::string PLogOpen(const char *log);
    bool PLogClose(std::string h);
	bool PLogWrite(int type, std::string h, const char *log, unsigned short logLen);
    bool PLogWriteHex(int type, std::string h, const char *prefix, const char *data, unsigned short dataLen);

};
