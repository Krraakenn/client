#include "kclient.hpp"

int main()
{
    const char *server_ip = "127.0.0.1"; // or the server IP address
    int server_port = 8080;

    Kclient client(server_ip, server_port);

    if (client.connectToServer())
    {
        client.sendMessage("Hello, server!");
    }

    return 0;
}
