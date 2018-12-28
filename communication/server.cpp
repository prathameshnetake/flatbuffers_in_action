/*
    Copyright 2016 AITOE
*/

#include "server.h"

void Server::startBoost(void (*session)(socket_ptr), boost::asio::io_service& io_service, short boostPort) {
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), boostPort));
    for (;;) {
        socket_ptr sock(new tcp::socket(io_service));
        a.accept(*sock);
        boost::thread t(boost::bind(session, sock));
    }
}
