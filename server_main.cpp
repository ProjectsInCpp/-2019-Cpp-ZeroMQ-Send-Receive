#include "ZeroMqUtils.hpp"

void singleRequestSingleReceive(int numberOfRequests)
{
   zmq::context_t context(1);
   zmq::socket_t socket (context, zmq::socket_type::req);
   socket.connect(TCP_ADDRESS.data());
   for (int requestId = 0; requestId != numberOfRequests; requestId++) {
      s_send(socket, MESSAGE_TO_SEND.data());
      std::string receivedMessage = s_recv(socket);
      std::cout << requestId << " - Received Message: " << receivedMessage << '\n';
   }
   socket.close();
}

void publishSubscribe()
{
   zmq::context_t context(1);
   zmq::socket_t socket (context, zmq::socket_type::pub);
   socket.bind(IPC_ADDRESS.data());
   while(true)
   {
      s_send(socket, RECEIVER_ADDRESS.data(), zmq::send_flags::sndmore);
      s_send(socket, MESSAGE_TO_SEND.data(), zmq::send_flags::sndmore);
      s_send(socket, MESSAGE_TO_SEND.data());
      std::this_thread::sleep_for(std::chrono::seconds(MESSAGE_INTERVAL));
   }
}

int main (void)
{
//   singleRequestSingleReceive(10);
   publishSubscribe();
   return 0;
}
