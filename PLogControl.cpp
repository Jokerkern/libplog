#include "PLogControl.h"
std::shared_ptr<webSocketControl> g_webSocketControl = std::make_shared<webSocketControl>();
PLogControl::PLogControl() {

}


PLogControl::~PLogControl() {
}
void *PLogControl::logFlush(void* data) {
    spdlog::logger *logger = (spdlog::logger *)data;
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        //std::cout << "flush" << std::endl;
        if (logger) logger->flush();
        else break;
    }
    return data;
}
HANDLE PLogControl::PLogOpen(const char *log) {
    AutoLock lock(pLock);
    //std::cout << "open" << std::endl;
    //std::ofstream fout;
    //fout.open("dir.txt", std::ios::out | std::ios::app);
    //fout << log << std::endl;
    //fout.close();
    PLogConfig& config = PLogConfig::get_instance();
    //std::cout << config.getTcpPort() << " " << config.getTcpIp() << " " << config.getMode() << " " <<std::endl;
    //spdlog::sinks::tcp_sink_config cfg(config.getTcpIp(), config.getTcpPort());
    spdlog::sinks::tcp_sink_config cfg(config.getTcpIp(), config.getTcpSinkPort());
    std::vector<spdlog::sink_ptr> sinks;
    if ((config.getMode() & 1) != 0) {
        //std::cout << "tcp" <<std::endl;
        auto tcp_sink = std::make_shared<spdlog::sinks::tcp_sink_mt>(cfg);
        sinks.push_back(tcp_sink);
    }
    if ((config.getMode() & 2) != 0) {
        //std::cout << "ws" <<std::endl;
        auto websocket_sink = std::make_shared<spdlog::sinks::websocket_sink_mt>(g_webSocketControl);
        sinks.push_back(websocket_sink);
    }
    if ((config.getMode() & 4) != 0) {
        //std::cout << "fs" <<std::endl;
        //auto max_size = 1048576 * 0.005;
        //auto max_files = 1;
        char path[1024] = {};
        strcat(path, "./log/");
    	strcat(path, log);
    	
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, config.getMaxSize(), config.getMaxFiles());
        sinks.push_back(file_sink);
    }
    auto logger = std::make_shared<spdlog::logger>(log, sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::trace);
    spdlog::register_logger(logger);
    pthread_t t;
    pthread_create(&t,0,logFlush,logger.get());
    this->loggerList.push_back(logger.get());
    return logger.get();
}

bool PLogControl::PLogWrite(int type, HANDLE h, const char *log, unsigned short logLen) {
    //std::cout << "write" << type << PLogControl::LOG_LEVEL_DEBUG << std::endl;
    spdlog::logger *logger = (spdlog::logger *)h;
    if (!loggerIsValid(logger)) return false;
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
    //spdlog::flush_every(std::chrono::seconds(3));
    //logger->flush();
    return true;
}

bool PLogControl::PLogWriteHex(int type, HANDLE h, const char *prefix, const char *data, unsigned short dataLen) {
    //std::cout << "write" << prefix << std::endl;
    return false;
}

bool PLogControl::PLogClose(HANDLE h) {
    //std::cout << "close" << std::endl;
    if(h == NULL)
        return false;
    AutoLock lock(pLock);
    loggerList.remove((spdlog::logger *)h);
    delete (spdlog::logger *)h;
    return true;
}

bool PLogControl::loggerIsValid(spdlog::logger *logger) {
    bool bFind = false;
    for(auto iter = loggerList.begin(); iter != loggerList.end(); iter++)
    {
        if(*iter == logger)
        {
            bFind = true;
            break;
        }
    }
    return bFind;
}

void* PLogControl::webServer(void* data){
    httpServer httpserver;
    httpserver.run();
    //std:: << "webserver" << std::endl;
    return data;
}

void* PLogControl::webSocket(void* data) {
    g_webSocketControl->run(9002);
    //std::cout << "websocket" << std::endl;
    return data;
}

bool PLogControl::StartThread() {
    pthread_t t1, t2;
    pthread_create(&t1,0,webSocket,NULL);
    pthread_create(&t2,0,webServer,NULL);
    return true;
    //pthread_detach(t2);
    //pthread_detach(t1);
}

bool PLogControl::StopThread()  {
    return true;
}
