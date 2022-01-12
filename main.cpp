/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 28 Dec 2021 12:38:28 AM PST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include "LogWrapper.h"
using namespace std;
    
    
    
    
void testLog(size_t i){

    LogWrapper *logger = new LogWrapper;
    std::string res = std::to_string(i);
    logger->Open(res.c_str());

    size_t count = 0;
    while (true){
        logger->Write(3, "%s log : %d", res.c_str(), count++);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    LogWrapper::Load();
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; ++i){
        threads.push_back(std::thread(testLog, i)) ;
    }

    for (auto& t: threads) {
        t.join();
    }
    return 0;
}
