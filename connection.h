#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr

#define PORT 8000

int create_socket();
void setup_server(struct sockaddr_in* server);
void bind_server_to_socket(int socket_desc, struct sockaddr_in* server);
