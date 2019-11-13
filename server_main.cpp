#include "ZeroMqUtils.hpp"
#include <iostream>
#include <thread>

void singleRequestSingleReceive()
{
   zmq::context_t context(1);
   zmq::socket_t socket (context, zmq::socket_type::req);
   socket.connect("tcp://127.0.0.1:5555");
   for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
      s_send(socket, "DUPAAA");
      std::string receivedMessage = s_recv(socket);
      std::cout << request_nbr << " - Received Message: " << receivedMessage << std::endl;
   }
   socket.close();
}

void publishSubscribe(int numberOfRequests)
{
   zmq::context_t context(1);
   std::cout << __func__ << "1" << std::endl;
   zmq::socket_t socket (context, zmq::socket_type::pub);
   std::cout << __func__ << "2" << std::endl;
   socket.connect("tcp://127.0.0.1:5555");
   std::cout << __func__ << "3" << std::endl;
   while(true)
   {
      zmq::message_t message(3);
      memcpy (message.data(), "123", 3);
      const auto retCode = socket.send (message, zmq::send_flags::none);
      std::cout << "Sent message : " << message << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
}

int main (void)
{
//   singleRequestSingleReceive();
   publishSubscribe(10);
   return 0;
}
