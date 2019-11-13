#pragma once

#include <zmq.hpp>
#include <string>
#include <iostream>

static std::string s_recv (
        zmq::socket_t & socket, zmq::recv_flags flags = zmq::recv_flags::none)
{
   zmq::message_t message;
   socket.recv(message, flags);
   return std::string(static_cast<char*>(message.data()), message.size());
}

static bool s_send (zmq::socket_t & socket, const std::string & string,
        zmq::send_flags flags=zmq::send_flags::none)
{
   zmq::message_t message(string.size());
   memcpy (message.data(), string.data(), string.size());
   const auto retCode = socket.send (message, flags);
   return retCode.has_value();
}
