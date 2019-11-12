#include "ZeroMqUtils.hpp"
#include <iostream>
#include <unistd.h>

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("ipc:///tmp/test");

    while (true) {
        std::string message = s_recv(socket);
        std::cout << "Received Message: " << message << std::endl;
        //  Do some 'work'
        sleep (1);
        s_send(socket, "WorldOfDupa");
    }
    return 0;
}
