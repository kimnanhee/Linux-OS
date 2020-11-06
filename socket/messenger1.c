#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

#define SIZE sizeof(struct sockaddr_in)
#define MAX_SIZE 2048

//#define MY_PORT_S 2008
//#define MY_PORT_R 2009

void *recvMsg(void *parms);
int sendMsg(char *msg, int size, char* ip, int port);
int sendMsg2(char *msg, int size, struct sockaddr* sock, int sock_len);

int MY_PORT_S, MY_PORT_R;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("usage : %s my_port_s my_port_r target_port_r\n", argv[0]);
        exit(0);
    }

    MY_PORT_S = atoi(argv[1]);
    MY_PORT_R = atoi(argv[2]);
    int target_r = atoi(argv[3]);

    pthread_t tid;
    if (pthread_create(&tid, NULL, recvMsg, NULL))
    {
        printf("thread create fail\n");
    }

    while (1)
    {
        char msg[MAX_SIZE];
        fgets(msg, MAX_SIZE, stdin);
        sendMsg(msg, strlen(msg), "127.0.0.1", target_r);
    }
}

void* recvMsg(void* parms)
{
    struct sockaddr_in mySock = {AF_INET, htons(MY_PORT_R), INADDR_ANY};
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = bind(sockfd, (struct sockaddr*)&mySock, sizeof(mySock));
    if (ret < 0)
    {
        extern int errno;
        printf("ret(%d), errno(%d, %s)\n", ret, errno, strerror(errno));
    }   

    int sock_len;
    char msg[MAX_SIZE];
    while (1)
    {
        struct sockaddr_in sock;
        memset(msg, 0, MAX_SIZE);
        int ret = recvfrom(sockfd, &msg, MAX_SIZE, 0, (struct sockaddr*)&sock, &sock_len);
        if (ret < 0)
        {
            extern int errno;
            printf("ret(%d), errno(%d, %s)\n", ret, errno, strerror(errno));
        }
        else
        {
            printf("msg : %s\n", msg);
        }
    }
    close(sockfd);
}

int sendMsg2(char *msg, int size, struct sockaddr* sock, int sock_len)
{
    struct sockaddr_in mySock = {AF_INET, htons(MY_PORT_S), INADDR_ANY};
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = bind(sockfd, (struct sockaddr*)&mySock, sizeof(mySock));
    if (ret < 0)
    {
        extern int errno;
        printf("ret(%d), errno(%d, %s)\n", ret, errno, strerror(errno));
    }  
    sendto(sockfd, msg, size, 0, sock, sock_len);
    close(sockfd);
}

int sendMsg(char *msg, int size, char* ip, int port)
{
    struct sockaddr_in mySock = {AF_INET, htons(MY_PORT_S), INADDR_ANY};
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = bind(sockfd, (struct sockaddr*)&mySock, sizeof(mySock));
    if (ret < 0)
    {
        extern int errno;
        printf("ret(%d), errno(%d, %s)\n", ret, errno, strerror(errno));
    }
    struct sockaddr_in sock = {AF_INET, htons(port), INADDR_ANY};
    sendto(sockfd, msg, size, 0, (struct sockaddr*)&sock, sizeof(sock));
    close(sockfd);
}