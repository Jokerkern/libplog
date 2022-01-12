#ifndef _PLOGCONFIG_H_
#define _PLOGCONFIG_H_
#include <iostream>
#include <cstring>
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
    static char *get_conf_value(const char *filename, const char *key);
    int getMode();
    int getTcpSinkPort();
    int getTcpHttpPort();
    int getBufferSize();
    int getMaxSize();
    int getMaxFiles();
    std::string getTcpIp();
private:
    int mode, tcpSinkPort, tcpHttpPort, bufferSize;
    int maxFiles, maxSize;
    std::string tcpIp;
    const char *config = "./plog.conf";
    PLogConfig(){
        mode = atoi(get_conf_value(config, "MODE"));
        tcpIp = get_conf_value(config, "TCPIP");
        tcpSinkPort = atoi(get_conf_value(config, "TCPSINKPORT"));
        tcpHttpPort = atoi(get_conf_value(config, "TCPHTTPPORT"));
        bufferSize = atoi(get_conf_value(config, "BUFFERSIZE"));
        maxFiles = atoi(get_conf_value(config, "MAXFILES"));
        maxSize = atoi(get_conf_value(config, "MAXSIZE"));
        //std::cout<<"constructor called!"<<std::endl;
    }

};

#endif
