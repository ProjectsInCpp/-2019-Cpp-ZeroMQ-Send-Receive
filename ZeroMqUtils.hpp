#pragma once

#include <zmq.hpp>
#include <string>

static std::string s_recv (zmq::socket_t & socket) {

   zmq::message_t message;
   socket.recv(message, zmq::recv_flags::none);
   return std::string(static_cast<char*>(message.data()), message.size());
}

static bool s_send (zmq::socket_t & socket, const std::string & string) {

   zmq::message_t message(string.size());
   memcpy (message.data(), string.data(), string.size());
   const auto retCode = socket.send (message, zmq::send_flags::none);
   return retCode.has_value();
}
