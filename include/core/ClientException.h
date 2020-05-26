#pragma once

class ClientException: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ClientConnectionAlreadyClosed: public ClientException
{
public:
    ClientConnectionAlreadyClosed()
        : ClientException("Connection has already closed")
    {}
};