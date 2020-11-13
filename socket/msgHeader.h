#ifndef __MSG_HEADER_H__
#define __MSG_HEADER_H__

// define port
#define PORT_SERVER_S 2001
#define PORT_SERVER_R 2002
#define PORT_CLIENT_S 2003
#define PORT_CLIENT_R 2004

// define msg id
#define reqGetEnv 0x00010001
#define rspGetEnv 0x00010002
#define reqSetEnv 0x00010002
#define rapSetEnv 0x00010003

// define msg structure
#include <arpa/inet.h>

inline int Write(int x) { return (htonl(x)); }
inline unsigned int Write(unsigned int x) { return (htonl(x)); }
inline short int Write(short int x) { return (htons(x)); }
inline short unsigned int Write(short unsigned int x) { return (htons(x)); }

inline int Read(int x) { return (ntohl(x)); }
inline unsigned int Read(unsigned int x) { return (ntohl(x)); }
inline short int Read(short int x) { return (ntohs(x)); }
inline short unsigned int Read(short unsigned int x) { return (ntohs(x)); }

struct msgHeader
{
	int cmdId;
};
inline void Write(struct msgHeader &x)
{
	x.cmdId = Write(x.cmdId);
}
inline void Read(struct msgHeader &x)
{
    x.cmdId = Read(x.cmdId);
}

#define MAX_ENV 256
struct dataEnv
{
    char envName[MAX_ENV];
    char envValue[MAX_ENV];
    int retValue;
};

inline void Write(struct dataEnv &x)
{
    x.retValue = Write(x.retValue);
};

inline void Read(struct dataEnv &x)
{
    x.retValue = Read(x.retValue);
};

struct msgEnv
{
    struct msgHeader hdr;
    struct dataEnv env;
};

inline void Write(struct msgEnv &x)
{
    Write(x.hdr);
    Write(x.env);
}

inline void Read(struct msgEnv &x)
{
    Read(x.hdr);
    Read(x.env);
}

#endif // __MSG_HEADER_H__
