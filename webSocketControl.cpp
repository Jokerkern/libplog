#include "webSocketControl.h"

webSocketControl::webSocketControl() {
    PLogConfig& config = PLogConfig::get_instance();
    listSize = config.getBufferSize();
    // Initialize Asio Transport
    m_server.set_reuse_addr(true);
    m_server.init_asio();

    // Register handler callbacks
    m_server.set_open_handler(bind(&webSocketControl::on_open, this, ::_1));
    m_server.set_close_handler(bind(&webSocketControl::on_close, this, ::_1));
    m_server.set_message_handler(bind(&webSocketControl::on_message, this, ::_1, ::_2));
    m_server.clear_access_channels(websocketpp::log::alevel::all);

}

void webSocketControl::run(uint16_t port) {
    // listen on specified port
    m_server.listen(port);

    // Start the server accept loop
    m_server.start_accept();

    // Start the ASIO io_service run loop
    try {
        m_server.run();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void webSocketControl::on_open(connection_hdl hdl) {
//
//    std::ifstream din("dir.txt");
//    std::string addr;
//    std::string line;
//    std::unordered_set<std::string> addrs;
//    while (getline(din, addr)) {
//
//        addrs.insert(addr);
//    }
//    din.close();
//    std::ofstream dout("dir.txt", std::ios::trunc | std::ios::out);
//    for (auto& i : addrs) {
//        dout << i << std::endl;
//    }
//    dout.close();
//    for (auto& a : addrs) {
//        std::cout << a  << std::endl;
//        std::ifstream fin(a);
//        while (getline(fin, line)) {
//            //std::cout << a  << std::endl;
//            m_server.send(hdl, line, websocketpp::frame::opcode::text);
//        }
//        std::cout << "close" << std::endl;
//        fin.close();
//    }
    AutoLock lock(pLock);
    for (std::string str : logList) {
        m_server.send(hdl, str, websocketpp::frame::opcode::text);
    }
    m_connections.insert(hdl);
}

void webSocketControl::on_close(connection_hdl hdl) {
    m_connections.erase(hdl);
}

void webSocketControl::on_message(connection_hdl hdl, server::message_ptr msg) {
    //msg->get_payload();
}
void webSocketControl::sendData(const char* msg) {
    con_list::iterator it;
    AutoLock lock(pLock);
    if (tempSize < listSize) {
        logList.push_back(msg);
        tempSize++;
    } else {
        logList.pop_front();
        logList.push_back(msg);
    }
    for (it = m_connections.begin(); it != m_connections.end(); ++it) {
        m_server.send(*it, msg, websocketpp::frame::opcode::text);
    }
}

