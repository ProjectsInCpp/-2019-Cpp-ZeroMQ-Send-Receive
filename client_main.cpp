#include "ZeroMqUtils.hpp"
#include <iostream>
#include <thread>

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
   zmq::socket_t socket (context, zmq::socket_type::sub);
   std::cout << __func__ << "2" << std::endl;
   socket.bind("tcp://127.0.0.1:5555");
   std::cout << __func__ << "3" << std::endl;
   while (true) {
//      std::string message = s_recv(socket, zmq::recv_flags::none);
      zmq::message_t message;
      socket.recv(message, zmq::recv_flags::dontwait);
//      return std::string(static_cast<char*>(message.data()), message.size());
      std::cout << "Received message: " << message.str() << std::endl;
//      s_send(socket, "DUPAA");
      std::this_thread::sleep_for(std::chrono::seconds(1));
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
