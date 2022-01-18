//
// Created by p on 12/23/21.
//

#ifndef PLOG_HTTPSERVER_H
#define PLOG_HTTPSERVER_H
#include "httpserver.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include "PLogConfig.h"
class httpServer {
public:
    static void run(int port) ;
};


#endif //PLOG_HTTPSERVER_H
