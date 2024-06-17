#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

class Kclient
{
public:
    Kclient(const char *server_ip, int server_port);
    ~Kclient();

    bool connectToServer();
    bool sendMessage(const char *message);

private:
    int clientSocket;
    sockaddr_in serverAddress;
};

Kclient::Kclient(const char *server_ip, int server_port)
{
    // creating socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // specifying address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(server_port);
    serverAddress.sin_addr.s_addr = inet_addr(server_ip);
}

Kclient::~Kclient()
{
    // closing socket
    close(clientSocket);
}

bool Kclient::connectToServer()
{
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return false;
    }
    return true;
}

bool Kclient::sendMessage(const char *message)
{
    if (send(clientSocket, message, strlen(message), 0) < 0)
    {
        std::cerr << "Send failed" << std::endl;
        return false;
    }
    return true;
}