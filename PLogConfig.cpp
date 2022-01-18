#include "PLogConfig.h"

std::unordered_map<std::string, std::string> PLogConfig::get_conf_value(const char *filename) {
    AutoLock lock(pLock);
    size_t pos;
    std::string line;
    std::unordered_map<std::string, std::string> m;
    std::ifstream  file(filename, std::ios::in);
    setting = "{";
    while (getline(file, line)) {
        if ((pos = line.find('=')) == line.npos) continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.size());
        m[key] = value;
        setting += "\"" + key + "\":\"" + value +"\",";
    }
    setting[setting.size() - 1] = '}';
    return m;
}

void PLogConfig::set_conf_value(std::string key, std::string value) {
    AutoLock lock(pLock);
    if (m.empty()) return;
    m[key] = value;
    std::ofstream file("plog.conf", std::ios::out | std::ios::trunc );
    setting = "{";
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        file << iter->first + "=" + iter->second << std::endl;
        setting += "\"" + key + "\":\"" + value +"\",";
    }
    setting[setting.size() - 1] = '}';
    file.close();
    change++;
}

void PLogConfig::set_conf_value(std::unordered_map<std::string, std::string> tm) {
    AutoLock lock(pLock);
    if (m.empty()) return;
    m = tm;
    std::ofstream file("plog.conf", std::ios::out | std::ios::trunc );
    setting = "{";
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        file << iter->first + "=" + iter->second << std::endl;
        setting += "\"" + iter->first + "\":\"" + iter->second +"\",";
    }
    setting[setting.size() - 1] = '}';
    file.close();
    change++;
}

bool PLogConfig::checkChange(std::string logger) {
    AutoLock lock(pLock);
    if (plogControlMap[logger] < change) {
        plogControlMap[logger] = change;
        return true;
    }
    return false;
}

int PLogConfig::getMode() {
    return atoi(m["MODE"].c_str());
}

int PLogConfig::getWebSocketPort() {
    return atoi(m["WEBSOCKETPORT"].c_str());
}

int PLogConfig::getTcpSinkPort() {
    return atoi(m["TCPSINKPORT"].c_str());
}

int PLogConfig::getTcpHttpPort() {
    return atoi(m["TCPHTTPPORT"].c_str());
}

int PLogConfig::getHttpPort() {
    return atoi(m["HTTPPORT"].c_str());
}

int PLogConfig::getBufferSize() {
    return atoi(m["BUFFERSIZE"].c_str());
}

int PLogConfig::getMaxFiles() {
    return atoi(m["MAXFILES"].c_str());
}

int PLogConfig::getMaxSize() {
    return atoi(m["MAXSIZE"].c_str()) * 1048576;
}

std::string PLogConfig::getTcpIp() {
    return m["TCPIP"];
}

std::string PLogConfig::getSetting() {
    return setting;
}
