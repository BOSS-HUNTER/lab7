#pragma once

#include <boost/unordered_map.hpp>
#include <boost/regex.hpp>

#include "Client.h"
#include "MessageHandlerException.h"

class Server;

class MessageHandler
{
public:
    using HandlerFunction = std::string (*)(const std::string &, Server &, Client &);
    using HandlersType = boost::unordered_map<std::string, HandlerFunction>;

    static std::string passMessage(const std::string& message, Server &server, Client &client);

private:
    static const HandlersType handlers;
};