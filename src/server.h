#include "datastore.h"

#ifndef SERVER_H
#define SERVER_H

class Server {
private:
    int port;
    int server_fd;
    DataStore datastore;

public:
    Server(int port);
    void start();
};

#endif