#include "server.h"
#include "datastore.h"
#include "parser.h"

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

Server::Server(int port) : port(port) {}

void Server::start()
{
    DataStore datastore;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        std::cerr << "Socket creation failed\n";
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed\n";
        return;
    }

    if (listen(server_fd, 5) < 0)
    {
        std::cerr << "Listen failed\n";
        return;
    }

    std::cout << "Server listening on port " << port << "\n";

    while (true)
    {
        int addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        if (client_socket < 0)
        {
            std::cerr << "Accept failed\n";
            continue;
        }

        char buffer[1024];

        while (true)
        {
            memset(buffer, 0, sizeof(buffer));

            int bytes_read = read(client_socket, buffer, sizeof(buffer));
            if (bytes_read <= 0) break;

            std::string input(buffer);
            std::vector<std::string> tokens = Parser::parseRESP(input);

            if (tokens.empty()) continue;

            std::string command = tokens[0];

            if (command == "SET" && tokens.size() >= 3) {
                std::string key = tokens[1];
                std::string value = tokens[2];
                int ttl = -1;

                if (tokens.size() >= 5 && tokens[3] == "EX") {
                    ttl = std::stoi(tokens[4]);
                }

                datastore.set(key, value, ttl);

                std::string response = "+OK\r\n";
                send(client_socket, response.c_str(), response.size(), 0);
            }
            else if (command == "GET" && tokens.size() >= 2)
            {
                std::string value = datastore.get(tokens[1]);

                if (value == "(nil)")
                {
                    std::string response = "$-1\r\n";
                    send(client_socket, response.c_str(), response.size(), 0);
                }
                else
                {
                    std::string response =
                        "$" + std::to_string(value.size()) + "\r\n" +
                        value + "\r\n";

                    send(client_socket, response.c_str(), response.size(), 0);
                }
            }
            else
            {
                std::string response = "-ERROR unknown command\r\n";
                send(client_socket, response.c_str(), response.size(), 0);
            }
        }

        close(client_socket);
    }
}