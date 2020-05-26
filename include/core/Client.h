#pragma once

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include "ClientException.h"

class Client
{
public:
    static const int TIMEOUT;

    using Socket = boost::asio::ip::tcp::socket;
    using StreamBuffer = boost::asio::streambuf;
    using Buffer = boost::asio::mutable_buffer;
    using ErrorCode = boost::system::error_code;
    using Context = boost::asio::io_context;
    using DeadlineTimer = boost::asio::deadline_timer;

    Client(Socket socket, const std::shared_ptr<Context>& ioContext)
        : socket_(std::move(socket)),
          deadline_(*ioContext),
          ioContext_(ioContext)
    {}

    Socket &getSocket()
    {
        return socket_;
    }

    void close()
    {
        socket_.close();
    }

    [[nodiscard]] bool isClosed() const
    {
        return !socket_.is_open();
    }

    [[nodiscard]] const std::string &getName() const
    {
        return name_;
    }

    void setName(const std::string &name)
    {
        name_ = name;
    }

    void readWithTimeout(StreamBuffer &buffer);

    void writeWithTimeout(const Buffer &buffer);

    [[nodiscard]] bool isUpdateList() const
    {
        return updateList_;
    }

    [[nodiscard]] bool isTimedOut() const
    {
        return isTimedOut_;
    }

    void setUpdateList(bool updateList)
    {
        updateList_ = updateList;
    }

    static void checkDeadline(std::weak_ptr<Client> client);
private:

    bool isTimedOut_ = false;
    bool updateList_ = false;

    Socket socket_;
    DeadlineTimer deadline_;
    std::shared_ptr<Context> ioContext_;
    std::string name_{};
};