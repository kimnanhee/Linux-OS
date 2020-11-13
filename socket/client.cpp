//client
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

#include "msgHeader.h"

#define SIZE sizeof(struct sockaddr_in)
#define MAX_SIZE 2048

void *recvMsg(void *parms);
int sendMsg(char *msg, int size, char *ip, int port);
int sendMsg2(char *msg, int size, struct sockaddr* sock, int sock_len);

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, recvMsg, NULL))
    {
        printf("thread create fail\n");
    }

    struct msgEnv mEnv;
    mEnv.hdr.cmdId = reqSetEnv;
    strcpy(mEnv.env.envName, "TESTENV");
    strcpy(mEnv.env.envValue, "TESTENV_VALUE");
    Write(mEnv);
    sendMsg((char*)&mEnv, sizeof(mEnv), (char*)"127.0.0.1", PORT_SERVER_R);

    sleep(5);
    mEnv.hdr.cmdId = reqGetEnv;
    strcpy(mEnv.env.envName, "TESTENV");
    strcpy(mEnv.env.envValue, "");
    Write(mEnv);
    sendMsg((char*)&mEnv, sizeof(mEnv), (char*)"127.0.0.1", PORT_SERVER_R);

    while(1)
        sleep(1);
}

void *recvMsg(void *parms)
{
    struct sockaddr_in mySock = {AF_INET, htons(PORT_CLIENT_R), INADDR_ANY};
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int ret = bind(sockfd, (struct sockaddr *) &mySock, sizeof(mySock));
	if(ret < 0)
	{
		extern int errno;
		printf("ret(%d), errno(%d, %s)\n", ret, errno, strerror(errno));
	}
	struct sockaddr_in sock;
	int sock_len;
	char msg[MAX_SIZE];
	while(1)
	{
		memset(msg, 0, MAX_SIZE);
		int ret = recvfrom(sockfd, &msg, MAX_SIZE, 0, (struct sockaddr *) &sock, (socklen_t*) &sock_len);
		if(ret < 0)
		{
			extern int errno;
			printf("ret(%d), errno(%d, %s)\n", ret, errno, strerror(errno));
		}
		else 
		{
			printf("%d msg received\n", ret);
            struct msgHeader hdr = *(struct msgHeader *)msg;
            Read(hdr);
            switch(hdr.cmdId)
            {
                case reqGetEnv:
                {
                    printf("Rsp Get Env\n");
                    struct dataEnv data = *(struct dataEnv *) (msg + sizeof(struct msgHeader));
                    
                    Read(data);
                    strcpy(data.envValue, getenv(data.envValue));
                    printf("%s %s\n", data.envName, data.envValue);
                    break;
                }
                case reqSetEnv:
                {
                    printf("Rsp Set Env\n");
                    struct dataEnv data = *(struct dataEnv *) (msg + sizeof(struct msgHeader));

                    Read(data);
                    printf("%s %s\n", data.envName, data.envValue);
                    break;
                }
                default:
                    break;
            }
		}
	}
	close(sockfd);
}

int sendMsg2(char *msg, int size, struct sockaddr* sock, int sock_len)
{
    struct sockaddr_in mySock = {AF_INET, htons(PORT_SERVER_S), INADDR_ANY};
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = bind(sockfd, (struct sockaddr *)&mySock, sizeof(mySock));
    if(ret < 0)
    {
        extern int errno;
        printf("ret(%d), errno(%d. %s)\n", ret, errno, strerror(errno));
    }
    sendto(sockfd, msg, size, 0, sock, sock_len);
    close(sockfd);
    return 0;
}

int sendMsg(char *msg, int size, char *ip, int port)
{
    struct sockaddr_in mySock = {AF_INET, htons(PORT_SERVER_S), INADDR_ANY};
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = bind(sockfd, (struct sockaddr *)&mySock, sizeof(mySock));
    if(ret < 0)
    {
        extern int errno;
        printf("ret(%d), errno(%d. %s)\n", ret, errno, strerror(errno));
    }

    struct sockaddr_in sock = {AF_INET, htons(port), INADDR_ANY};
    sock.sin_addr.s_addr = inet_addr(ip);

    sendto(sockfd, msg, size, 0, (struct sockaddr *)&sock, sizeof(sock));
    close(sockfd);
    return 0;
}