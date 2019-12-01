#include "ZeroMqUtils.hpp"

void singleRequestSingleReceive(int numberOfRequests)
{
   std::cout << __func__ << "Start" << '\n';
   zmq::context_t context{ NUM_OF_IO_THREADS };
   zmq::socket_t socket{context, zmq::socket_type::req };
   socket.connect(TCP_ADDRESS.data());
   for (int requestId = 0; requestId != numberOfRequests; requestId++) {
      s_send(socket, MESSAGE_TO_SEND.data());
      std::string receivedMessage{ s_recv(socket) };
      std::cout << requestId+1 << " - Received Message: " << receivedMessage << '\n';
   }
   socket.close();
   std::cout << __func__ << "End" << '\n';
}

void publishSubscribe(int numberOfRequests)
{
   std::cout << __func__ << "Start" << '\n';
   zmq::context_t context{ NUM_OF_IO_THREADS };
   zmq::socket_t socket{ context, zmq::socket_type::pub };
   socket.bind(TCP_ADDRESS.data());
   for (int requestId = 0; requestId != numberOfRequests; requestId++)
   {
      std::cout << __func__ << "Publish msg: " << requestId+1 << '\n';
      s_send(socket, RECEIVER_ADDRESS.data(), zmq::send_flags::sndmore);
      s_send(socket, MESSAGE_TO_SEND.data()+std::to_string(requestId), zmq::send_flags::sndmore);
      s_send(socket, MESSAGE_TO_SEND.data()+std::to_string(requestId));
      std::this_thread::sleep_for(std::chrono::seconds(MESSAGE_INTERVAL));
   }
   std::this_thread::sleep_for(std::chrono::seconds(3));
   std::cout << __func__ << "End" << '\n';
}

int main (void)
{
   int DIRTY_HACK_FOR_LOST_MESSAGE = 1;
   //singleRequestSingleReceive(10);
   publishSubscribe(2 + DIRTY_HACK_FOR_LOST_MESSAGE);
   return 0;
}
