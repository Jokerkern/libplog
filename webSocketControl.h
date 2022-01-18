#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/thread.hpp>
#include <iostream>
#include <set>
#include <list>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include "PLogConfig.h"
#include "AutoLock.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using websocketpp::lib::thread;
class webSocketControl {
public:
    webSocketControl();

	void run(uint16_t port);

	void on_open(connection_hdl hdl);

	void on_close(connection_hdl hdl);

	void on_message(connection_hdl hdl, server::message_ptr msg);
	void sendData(const char* msg);

private:
	typedef std::set<connection_hdl, std::owner_less<connection_hdl> > con_list;
    std::list<std::string> logList;
    int tempSize = 0;
	server m_server;
	con_list m_connections;
	Lock pLock;
};

