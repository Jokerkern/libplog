#include "PLogConfig.h"
char *PLogConfig::get_conf_value(const char *filename, const char *key) {
    char *conf_ans = (char *)calloc(1024, sizeof(char));
    bzero(conf_ans, sizeof(conf_ans));
    FILE *fp;
    char *line = NULL, *sub = NULL;
    size_t len = 0, nread = 0;
    if (filename == NULL || key == NULL) {
        return NULL;
    }
    if ((fp = fopen(filename, "r")) == NULL) {
        return NULL;
    }

    while ((nread = getline(&line, &len, fp)) != -1) {
        if ((sub = strstr(line, key)) == NULL) continue;
        if (line[strlen(key)] == '=' && sub == line) {
            strcpy(conf_ans, line + strlen(key) + 1);
            if (conf_ans[strlen(conf_ans) - 1] == '\n')
                conf_ans[strlen(conf_ans) - 1] = '\0';
        }
    }
    free(line);
    fclose(fp);
    return conf_ans;
}

int PLogConfig::getMode() {
    return mode;
}

int PLogConfig::getTcpSinkPort() {
    return tcpSinkPort;
}

int PLogConfig::getTcpHttpPort() {
    return tcpHttpPort;
}

int PLogConfig::getBufferSize() {
    return bufferSize;
}

int PLogConfig::getMaxFiles() {
    return maxFiles;
}

int PLogConfig::getMaxSize() {
    return maxSize;
}

std::string PLogConfig::getTcpIp() {
    return tcpIp;
}
