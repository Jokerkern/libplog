#include "PLogControl.h"
std::shared_ptr<webSocketControl> g_webSocketControl = std::make_shared<webSocketControl>();
PLogControl::PLogControl() {

}


PLogControl::~PLogControl() {
}
//void *PLogControl::logFlush(void* data) {
//
//    while (1) {
//        std::this_thread::sleep_for(std::chrono::seconds(3));
//        if (logger) logger->flush();
//        else break;
//    }
//    return data;
//}
std::string PLogControl::PLogOpen(const char *log) {
    AutoLock lock(pLock);
    PLogConfig& config = PLogConfig::get_instance();
    spdlog::sinks::tcp_sink_config cfg(config.getTcpIp(), config.getTcpSinkPort());
    std::vector<spdlog::sink_ptr> sinks;
    if ((config.getMode() & 1) != 0) {
        auto tcp_sink = std::make_shared<spdlog::sinks::tcp_sink_mt>(cfg);
        sinks.push_back(tcp_sink);
    }
    if ((config.getMode() & 2) != 0) {
        auto websocket_sink = std::make_shared<spdlog::sinks::websocket_sink_mt>(g_webSocketControl);
        sinks.push_back(websocket_sink);
    }
    if ((config.getMode() & 4) != 0) {
        char path[1024] = {};
        strcat(path, "./log/");
    	strcat(path, log);
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, config.getMaxSize(), config.getMaxFiles());
        sinks.push_back(file_sink);
    }
    std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(log, sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::trace);
    spdlog::register_logger(logger);
    //pthread_t t;
    //pthread_create(&t,0,logFlush,logger->name());
    this->loggerMap[logger->name()] = logger;
    return logger->name();
}

bool PLogControl::PLogWrite(int type, std::string h, const char *log, unsigned short logLen) {
    //std::cout << "write" << type << PLogControl::LOG_LEVEL_DEBUG << std::endl;
//    spdlog::logger *logger = (spdlog::logger *) h;
//    if (!loggerIsValid(logger)) return false;
    PLogConfig& config = PLogConfig::get_instance();
    if (config.checkChange(h)) {
        spdlog::drop_all();
        spdlog::sinks::tcp_sink_config cfg(config.getTcpIp(), config.getTcpSinkPort());
        std::vector<spdlog::sink_ptr> sinks;
        if ((config.getMode() & 1) != 0) {
            auto tcp_sink = std::make_shared<spdlog::sinks::tcp_sink_mt>(cfg);
            sinks.push_back(tcp_sink);
        }
        if ((config.getMode() & 2) != 0) {
            auto websocket_sink = std::make_shared<spdlog::sinks::websocket_sink_mt>(g_webSocketControl);
            sinks.push_back(websocket_sink);
        }
        if ((config.getMode() & 4) != 0) {
            char path[1024] = {};
            strcat(path, "./log/");
            strcat(path, h.c_str());
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, config.getMaxSize(), config.getMaxFiles());
            sinks.push_back(file_sink);
        }
        std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(h, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        spdlog::register_logger(logger);
        //std::cout << "dirty" << std::endl;
        loggerMap[h] = logger;
    }
    std::shared_ptr<spdlog::logger> logger = loggerMap[h];
    switch (type)
    {
        case PLogControl::LOG_LEVEL_DEBUG:
        //std::cout << "write" << type << PLogControl::LOG_LEVEL_DEBUG << std::endl;
            logger->debug(log);
            break;
        case PLogControl::LOG_LEVEL_ERROR:
            logger->error(log);
            break;
        case PLogControl::LOG_LEVEL_FATAL:
            logger->critical(log);
            break;
        case PLogControl::LOG_LEVEL_INFO:
            logger->info(log);
            break;
        default:
            break;
    }
    logger->flush();
    return true;
}

bool PLogControl::PLogWriteHex(int type, std::string h, const char *prefix, const char *data, unsigned short dataLen) {
    return false;
}

bool PLogControl::PLogClose(std::string h) {
    AutoLock lock(pLock);
    loggerMap.erase(h);
    return true;
}

void PLogControl::webServer(){
    PLogConfig& config = PLogConfig::get_instance();
    httpServer httpserver;
    httpserver.run(config.getHttpPort());
    return ;
}

void PLogControl::webSocket() {
    PLogConfig& config = PLogConfig::get_instance();
    g_webSocketControl->run(config.getWebSocketPort());
    return ;
}

bool PLogControl::StartThread() {
    thread t1(webSocket);
    thread t2(webServer);
    t1.detach();
    t2.detach();
    return true;
}

bool PLogControl::StopThread()  {
    return true;
}
