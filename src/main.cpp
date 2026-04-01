#include "server.h"

int main() {
    Server server(6379);  //redis default port
    server.start();
    return 0;
}