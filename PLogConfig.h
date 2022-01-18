#ifndef _PLOGCONFIG_H_
#define _PLOGCONFIG_H_
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <atomic>
#include "AutoLock.h"
class PLogConfig
{
public:
    ~PLogConfig(){
        //std::cout<<"destructor called!"<<std::endl;
    }
    PLogConfig(const PLogConfig&)=delete;
    PLogConfig& operator=(const PLogConfig&)=delete;
    static PLogConfig& get_instance(){
        static PLogConfig instance;
        return instance;

    }
    std::unordered_map<std::string, std::string> get_conf_value(const char *filename);
    void set_conf_value(std::string, std::string);
    void set_conf_value(std::unordered_map<std::string, std::string>);
    bool checkChange(std::string logger);
    int getMode();
    int getWebSocketPort();
    int getHttpPort();
    int getTcpSinkPort();
    int getTcpHttpPort();
    int getBufferSize();
    int getMaxSize();
    int getMaxFiles();
    std::string getTcpIp();
    std::string getSetting();
private:
    Lock pLock;
    int change = 0;
    const char *config = "./plog.conf";
    std::string setting;
    std::unordered_map<std::string, int> plogControlMap;
    std::unordered_map<std::string, std::string> m;
    PLogConfig() {
        m = get_conf_value(config);
    }

};

#endif
