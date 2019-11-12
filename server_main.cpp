#include "ZeroMqUtils.hpp"
#include <iostream>

int main (void)
{
  zmq::context_t context(1);

    printf ("Connecting to hello world server…\n");
    zmq::socket_t socket (context, ZMQ_REQ);
    socket.connect("ipc:///tmp/test");

    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
       s_send(socket, "DUPAA");
       std::string receivedMessage = s_recv(socket);
       std::cout << request_nbr << " - Received Message: " << receivedMessage << std::endl;
    }
    socket.close();
    return 0;
}
