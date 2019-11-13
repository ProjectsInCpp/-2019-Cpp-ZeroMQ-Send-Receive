#include "ZeroMqUtils.hpp"
#include <iostream>
#include <thread>

int
s_sendmore (void *socket, const char *string) {
   int size = zmq_send (socket, string, strlen (string), ZMQ_SNDMORE);
   return size;
}

void singleRequestSingleReceive()
{
   zmq::context_t context(1);
   zmq::socket_t socket (context, zmq::socket_type::req);
   socket.connect("tcp://127.0.0.1:5555");
   for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
      zmq::message_t message(3);
      memcpy (message.data(), "123", 3);
      std::cout << "Message before send: " << message << std::endl;
      s_send(socket, "DUPAAA", zmq::send_flags::dontwait);
      std::cout << "Message after send: " << message << std::endl;
      std::string receivedMessage = s_recv(socket);
      std::cout << request_nbr << " - Received Message: " << receivedMessage << std::endl;
   }
   socket.close();
}

void publishSubscribe(int numberOfRequests)
{
   zmq::context_t context(1);
   std::cout << __func__ << "1" << std::endl;
   zmq::socket_t socket (context, ZMQ_PUB);
   socket.bind("ipc://test");
   std::cout << __func__ << "2" << std::endl;
   std::cout << __func__ << "3" << std::endl;
   while(true)
   {
//      s_sendmore(socket, "B");
      s_send(socket, "My good message");
      std::this_thread::sleep_for(std::chrono::seconds(2));
   }
}

int main (void)
{
//   singleRequestSingleReceive();
   publishSubscribe(10);
   return 0;
}
