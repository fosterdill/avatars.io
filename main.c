/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "connection.h"
#include "pool.h"
#include "client.h"

#define LISTEN_QUEUE_SIZE 20

//the thread function
void *connection_handler(void *);

int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = create_socket();

    //Prepare the sockaddr_in structure
    setup_server(&server);

    bind_server_to_socket(socket_desc, &server);

    //Listen
    listen(socket_desc , LISTEN_QUEUE_SIZE);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    threadpool_t *pool = create_threadpool();

    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        puts("Connection accepted");

        if( threadpool_add(pool, connection_handler, (void*) &client_sock, 0))
        {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the threa
        puts("Handler assigned");
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    size_t buf_size;
    char *message , client_message[5000];

    // //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    puts("set message");
    puts(message);
    // write(sock , message , strlen(message));

    // message = "Now type something and i shall repeat what you type \n";
    // write(sock , message , strlen(message));

    //Receive a message from client
    buf_size = recv(sock , client_message , 5000 , 0);
    puts("receive buffer");
    puts(client_message);
        //end of string marker
    // client_message[buf_size] = '\0';

    //Send the message back to client
    download_jpeg("http://www.joomlaworks.net/images/demos/galleries/abstract/7.jpg");
    send(sock , message , strlen(message), 0);
    puts("send message");
    puts(message);

    close(sock);

    //clear the message buffer
    memset(client_message, 0, 5000);

    if(buf_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(buf_size == -1)
    {
        perror("recv failed");
    }

    return 0;
}

