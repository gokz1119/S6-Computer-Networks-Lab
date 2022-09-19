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
    int sockfd, confd, status;
    struct sockaddr_in server;
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

    confd = connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    if (confd < 0)
    {
        printf("Unable to connect\n");
        exit(0);
    }
    printf("Connection established\n");

    int n = 0;
    printf("Enter the string to be reversed: ");
    while((buff[n++] = getchar()) != '\n')
        ;
    status = send(sockfd, buff, sizeof(buff), 0);
    if(status < 0) {
        printf("Error in sending\n");
        exit(0);
    }

    printf("String sent to server\n");

    printf("Closing the connection\n");
    close(sockfd);
    return 0;
}