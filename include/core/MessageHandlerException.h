#pragma once

class MessageHandlerException: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class NoMessageFound: public MessageHandlerException
{
public:
    explicit NoMessageFound(const std::string &message)
        : MessageHandlerException("No valid regex for message '" + message + "'")
    {}
};