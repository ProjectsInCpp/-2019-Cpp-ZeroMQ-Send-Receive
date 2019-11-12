#include "ZeroMqUtils.hpp"
#include <iostream>
#include <thread>

int main () {
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("ipc:///home/pkorycin/my_port");
    while (true) {
        std::string message = s_recv(socket);
        std::cout << "Received Message: " << message << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        s_send(socket, "WorldOfDupa");
    }
    return 0;
}
