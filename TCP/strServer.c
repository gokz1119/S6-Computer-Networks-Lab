#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX 100

int main()
{
    int sockfd, confd, len, clilen;
    struct sockaddr_in server, client;
    char buff[MAX];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Unable to create socket\n");
        exit(0);
    }
    printf("Socket created\n");
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(5050);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) != 0)
    {
        printf("Unable to bind\n");
        exit(0);
    }
    printf("Binded\n");

    if (listen(sockfd, 5) != 0)
    {
        printf("Unable to listen");
        exit(0);
    }
    printf("Server is listening\n");

    clilen = sizeof(client);
    confd = accept(sockfd, (struct sockaddr *)&client, &clilen);

    if (confd < 0)
    {
        printf("Unable to accept\n");
        exit(0);
    }
    printf("Connection established\n");

    len = recv(confd, buff, sizeof(buff), 0);

    printf("The string from client is: %s", buff);
    printf("The reversed string is: ");
    for (int i = strlen(buff) - 1; i >= 0; i--)
    {
        printf("%c", buff[i]);
    }
    printf("\nClosing the connection\n");
    close(sockfd);
    return 0;
}