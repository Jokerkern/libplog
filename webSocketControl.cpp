#include "webSocketControl.h"

webSocketControl::webSocketControl() {
    // Initialize Asio Transport
    m_server.set_reuse_addr(true);
    m_server.init_asio();

    // Register handler callbacks
    m_server.set_open_handler(bind(&webSocketControl::on_open, this, ::_1));
    m_server.set_close_handler(bind(&webSocketControl::on_close, this, ::_1));
    m_server.set_message_handler(bind(&webSocketControl::on_message, this, ::_1, ::_2));
    m_server.set_access_channels(websocketpp::log::alevel::none);

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
    AutoLock lock(pLock);
    PLogConfig& config = PLogConfig::get_instance();
    m_server.send(hdl, config.getSetting(), websocketpp::frame::opcode::text);
    for (std::string str : logList) {
        m_server.send(hdl, str, websocketpp::frame::opcode::text);
    }
    m_connections.insert(hdl);
}

void webSocketControl::on_close(connection_hdl hdl) {
    m_connections.erase(hdl);
}

void webSocketControl::on_message(connection_hdl hdl, server::message_ptr msg) {
    //std::cout << msg->get_payload() << std::endl;
    bool type = true;
    size_t pos = -1;
    std::string payload = msg->get_payload(), key;
    std::unordered_map<std::string, std::string> m;
    while ((pos = payload.find('\"', pos + 1)) != payload.npos) {
        size_t pos2 = payload.find('\"', pos + 1);
        std::string temp = payload.substr(pos + 1, pos2 - pos - 1);
        pos = pos2;
        if (type == true) {
            key = temp;
            type = false;
        } else {
            m[key] = temp;
            type = true;
        }
    }
    PLogConfig& config = PLogConfig::get_instance();
    config.set_conf_value(m);
    sendData(config.getSetting().c_str());
    //config.set_conf_value("MODE", "3");
}
void webSocketControl::sendData(const char* msg) {
    AutoLock lock(pLock);
    PLogConfig& config = PLogConfig::get_instance();
    int listSize = config.getBufferSize();
    logList.push_back(msg);
    tempSize++;
    while (tempSize > listSize) {
        logList.pop_front();
        tempSize--;
    }
    for (auto it = m_connections.begin(); it != m_connections.end(); ++it) {
        m_server.send(*it, msg, websocketpp::frame::opcode::text);
    }
}

