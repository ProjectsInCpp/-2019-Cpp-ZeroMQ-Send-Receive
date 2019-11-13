#pragma once

#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <string>

constexpr uint8_t IS_ON = 1;
constexpr uint8_t MESSAGE_INTERVAL = 1;
constexpr uint8_t NUM_OF_IO_THREADS = 1;
std::string_view IPC_ADDRESS{"ipc://test"};
std::string_view TCP_ADDRESS{"tcp://127.0.0.1:5555"};
std::string_view RECEIVER_ADDRESS{"B"};
std::string_view MESSAGE_TO_SEND{"My message to send"};
std::string_view MESSAGE_TO_RECEIVE{"My message to receive"};

static std::string s_recv (
        zmq::socket_t & socket, zmq::recv_flags flags = zmq::recv_flags::none)
{
   zmq::message_t message;
   socket.recv(message, flags);
   return std::string(static_cast<char*>(message.data()), message.size());
}

static bool s_send (zmq::socket_t & socket, const std::string& string,
        zmq::send_flags flags=zmq::send_flags::none)
{
   zmq::message_t message(string.size());
   memcpy (message.data(), string.data(), string.size());
   return socket.send (message, flags).has_value();
}
