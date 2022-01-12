//
// Created by p on 12/23/21.
//

#include "httpServer.h"


typedef struct {
  int index;
  int len;
  int type;
} http_token_t;

typedef struct {
  http_token_t* buf;
  int capacity;
  int size;
} http_token_dyn_t;

typedef void (*epoll_cb_t)(struct epoll_event*);

typedef struct http_ev_cb_s {
  epoll_cb_t handler;
} ev_cb_t;

typedef struct {
  char* buf;
  int64_t total_bytes;
  int32_t capacity;
  int32_t length;
  int32_t index;
  int32_t anchor;
  http_token_t token;
  uint8_t flags;
} hs_stream_t;

typedef struct {
  int64_t content_length;
  int64_t body_consumed;
  int16_t match_index;
  int16_t header_count;
  int8_t state;
  int8_t meta;
} http_parser_t;

typedef struct http_request_s {
  epoll_cb_t handler;
  epoll_cb_t timer_handler;
  int timerfd;
  void (*chunk_cb)(struct http_request_s*);
  void* data;
  hs_stream_t stream;
  http_parser_t parser;
  int state;
  int socket;
  int timeout;
  struct http_server_s* server;
  http_token_dyn_t tokens;
  char flags;
} http_request_t;

typedef struct http_server_s {
  epoll_cb_t handler;
  epoll_cb_t timer_handler;
  int64_t memused;
  int socket;
  int port;
  int loop;
  int timerfd;
  socklen_t len;
  void (*request_handler)(http_request_t*);
  struct sockaddr_in addr;
  void* data;
  char date[32];
} http_server_t;

typedef struct http_header_s {
  char const * key;
  char const * value;
  struct http_header_s* next;
} http_header_t;

typedef struct http_response_s {
  http_header_t* headers;
  char const * body;
  int content_length;
  int status;
} http_response_t;

typedef struct http_string_s http_string_t;

void proxy(char * buf, int request) {
    int sd;
    struct sockaddr_in raddr;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    PLogConfig& config = PLogConfig::get_instance();
    if (sd < 0) {
        perror("socket()");
        return ;
    }
    raddr.sin_family = AF_INET;
    inet_pton(AF_INET, config.getTcpIp().c_str(), &raddr.sin_addr);
    raddr.sin_port = htons(config.getTcpHttpPort());
    if (connect(sd, (sockaddr *)&raddr, sizeof(raddr)) < 0) {
    	char buf[520]="HTTP/1.1 500 Internal Server Error\r\nconnection: close\r\n\r\n";
    	send(request, buf, strlen(buf), 0);
        perror("connect to collectionServer failed.");
        return ;
    }
    char recv_buf[1029] = {};
        if (send(sd, buf, strlen(buf), 0) < 0) {
            perror("send");
            return ;
        }
        //bool flag = true;
        //int cnt = 0;
        struct timeval tv_out;
    	tv_out.tv_sec = 3;
    	tv_out.tv_usec = 0;
    	setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));
        while (1) {
            memset(recv_buf, '\0', sizeof(recv_buf));
            int n = recv(sd, recv_buf, sizeof(recv_buf), 0);
            if (n <= 0) break;
            int m = send(request, recv_buf, n, 0);
            while (m < n) {
            	if (m < 0) {
            	    break;
            	}
            	n -= m;
            	m = send(request, recv_buf + m, n, 0);
            }
            usleep(100);
        //if (n < 1024 ) break;

            //cnt = 0;
        }
        //std::cout << "end" << std::endl;
        close(sd);


}

void handle_request(struct http_request_s* request) {
    std::string CodeFilestr, path = "./dist", type = "";
    std::ifstream  CodeInputStream;
    auto target = http_request_target(request);
    if (target.buf[3] == 'i') {
        //std::cout << "proxy" << std::endl;
        proxy(request->stream.buf, request->socket);
        close(request->socket);
        return;
    }
    for (int i = 0; i < target.len; i++) {
        path += target.buf[i];
    }
    if (target.len == 1) {
        path += "index.html";
        type = "text/html; charset=UTF-8";
    } else {
        for (int j = target.len - 1; target.buf[j] != '.'; j--) {
            type = target.buf[j] + type;
        }
        //std::cout << type << std::endl;
        if (type == "css") {
            type = "text/css; charset=UTF-8";
        } else if (type == "map") {
            type = "application/map; charset=UTF-8";
        } else if (type == "ico") {
            type = "image/icon; charset=UTF-8";
        } else if (type == "woff") {
            type = "font/woff; charset=UTF-8";
        } else if (type == "ttf") {
            type = "font/ttf; charset=UTF-8";
        } else {
            type = "application/javascript; charset=UTF-8";
        }
    }
    //std::cout << http_request_target(request).buf << std::endl;
    CodeInputStream.open(path.c_str()); // 参数一个const char*的字符串，代表文件的地址

    // 定义一个字符串流
    std::stringstream  CodeStrstream;

    // 把文件的输入流转换成字符串流
    CodeStrstream << CodeInputStream.rdbuf();

    // 关闭文件流
    CodeInputStream.close();

    // 转换字符串流到string
    CodeFilestr = CodeStrstream.str();
    struct http_response_s* response = http_response_init();
    http_response_status(response, 200);
    http_response_header(response, "Accept-Ranges", "bytes");
    http_response_header(response, "Content-Type", type.c_str());
    http_response_header(response, "Keep-Alive", "timeout=5");
    http_response_body(response, CodeFilestr.c_str(), CodeFilestr.length());
    http_respond(request, response);
}

void httpServer::run() {
    struct http_server_s* server = http_server_init(8080, handle_request);
    http_server_listen(server);
}
