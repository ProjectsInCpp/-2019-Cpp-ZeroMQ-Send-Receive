#include "ZeroMqUtils.hpp"

void singleReceiveSingleRequest()
{
   std::cout << __func__ << "Start" << '\n';
   zmq::context_t context{ NUM_OF_IO_THREADS };
   zmq::socket_t socket{context, zmq::socket_type::rep };
   socket.bind (TCP_ADDRESS.data());
   while (true) {
      std::string message{ s_recv(socket) };
      std::cout << "Received Message: " << message << '\n';
      std::this_thread::sleep_for(std::chrono::seconds(MESSAGE_INTERVAL));
      s_send(socket, MESSAGE_TO_RECEIVE.data());
   }
   std::cout << __func__ << "End" << '\n';
}

void publishSubscribe()
{
   std::cout << __func__ << "Start" << '\n';
   zmq::context_t context{ NUM_OF_IO_THREADS };
   zmq::socket_t socket{ context, zmq::socket_type::sub };
   socket.connect(TCP_ADDRESS.data());
   socket.setsockopt(ZMQ_SUBSCRIBE, RECEIVER_ADDRESS.data(), IS_ON);
   int msgCount = 0;
   while (true)
   {
      std::string messageAddresser{ s_recv(socket) };
      msgCount++;
      std::cout << "Message address: " << messageAddresser << '\n';
      std::string fstMsgData{ s_recv(socket) };
      std::cout << "Message id: " << msgCount << " - First message data: " << fstMsgData << '\n';
      std::string sndMsgData{ s_recv(socket) };
      std::cout << "Message id: " << msgCount << " - Second message data: " << sndMsgData << '\n' << '\n';
   }
   std::cout << __func__ << "End" << '\n';
}

int main ()
{
//   singleReceiveSingleRequest();
   publishSubscribe();
   return 0;
}
