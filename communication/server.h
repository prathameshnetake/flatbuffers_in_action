/*
    Copyright 2018 AITOE
*/

#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;
typedef boost::shared_ptr<tcp::socket> socket_ptr;



class Server {
public:
    static void startBoost(void (*session)(socket_ptr), boost::asio::io_service& io_service, short boostPort);
private:
};

#endif // SERVER_H
