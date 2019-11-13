#include "ZeroMqUtils.hpp"
#include <iostream>
#include <thread>

int
s_sendmore (void *socket, const char *string) {
   int size = zmq_send (socket, string, strlen (string), ZMQ_SNDMORE);
   return size;
}

void singleReceiveSingleRequest()
{
   zmq::context_t context (1);
   std::cout << "1" << std::endl;
   zmq::socket_t socket (context, zmq::socket_type::rep);
   std::cout << "2" << std::endl;
   socket.bind ("tcp://127.0.0.1:5555");
   std::cout << "3" << std::endl;
   while (true) {
      std::string message = s_recv(socket);
      std::cout << "Received Message: " << message << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      s_send(socket, "WorldOfDupa");
   }

}

void publishSubscribe()
{
   zmq::context_t context (1);
   std::cout << __func__ << "1" << std::endl;
   zmq::socket_t socket (context, ZMQ_SUB);
   std::cout << __func__ << "2" << std::endl;
   socket.connect("ipc://test");

   socket.setsockopt(ZMQ_SUBSCRIBE, "B", 1);

   std::cout << __func__ << "3" << std::endl;
   while (true) {
      std::string receivedMessage = s_recv(socket);
      std::cout << "Received message: " << receivedMessage << std::endl;
      std::string receivedMessage_2 = s_recv(socket);
      std::cout << "Received message_2: " << receivedMessage_2 << std::endl;
   }
}

int main ()
{
   std::cout << "Before everything" << std::endl;
//   singleReceiveSingleRequest();
   publishSubscribe();
   std::cout << "After everything" << std::endl;
   return 0;
}
