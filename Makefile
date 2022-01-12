all:
	g++ -fPIC -shared plog.cpp PLogControl.cpp webSocketControl.cpp httpserver.cpp httpServer.cpp PLogConfig.cpp -o libplog.so -I/home/p/Documents/spdlog/include -I/home/p/Documents/boost_1_70_0 -I/home/p/Documents/websocketpp -lpthread
	g++ main.cpp LogWrapper.cpp -ldl -lpthread
aarch64:
	aarch64-linux-gnu-g++-8 -fPIC -shared plog.cpp PLogControl.cpp webSocketControl.cpp httpserver.cpp httpServer.cpp PLogConfig.cpp -o libplog.so -I/home/p/Documents/spdlog/include -I/home/p/Documents/boost_1_70_0 -I/home/p/Documents/websocketpp -lpthread
	aarch64-linux-gnu-g++-8 main.cpp LogWrapper.cpp -ldl -lpthread
