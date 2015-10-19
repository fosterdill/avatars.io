#include "connection.h"

int create_socket() {
  int socket_desc = socket(AF_INET , SOCK_STREAM , 0);

  if (socket_desc == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  return socket_desc;
}

void setup_server(struct sockaddr_in* server) {
  server->sin_family = AF_INET;
  server->sin_addr.s_addr = INADDR_ANY;
  server->sin_port = htons(PORT);
}

void bind_server_to_socket(int socket_desc, struct sockaddr_in* server) {
  if(bind(socket_desc, (struct sockaddr *)server , sizeof(*server)) < 0) {
      perror("bind failed. Error");
      exit(1);
  }
}
