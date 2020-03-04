#pragma once

#include "GenericCPUBuffer.h"
    
#include <string>
#include <netinet/in.h>

typedef enum _SOCKET_STATUS
{
	SS_ACTIVATED,
	SS_INACTIVE
} SOCKET_STATUS;

typedef struct _IO_WRITE_OVERLAPPED
{
    char* buffer;
    int buflen;
    struct sockaddr_in addr;
    bool sent; // TODO: Is this needed?
} IO_WRITE_OVERLAPPED;

typedef enum _SOCKET_TYPE
{
	ST_NONE = 0,
	ST_TCP = 1,
	ST_UDP = 2
} SOCKET_TYPE;

typedef enum
{
	IOMT_NONE = 0,
	IOMT_TCP_CLIENT = 1,
	IOMT_TCP_SERVER = 2,
	IOMT_UDP_IO = 3
}IOModuleType;

typedef enum IO_STATE
{
	IO_CONNECTING,
	IO_CONNECTED,
	IO_DISCONNECTED
} IO_STATE;

//Open Socket
typedef void (*GERR_EVENT)          (void* socket, void* context, int errnum, char* msg, bool& shutdown);
typedef void (*RXIN_EVENT)          (void* socket, void* context, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);
typedef void (*TXIN_EVENT)          (void* socket, void* context, unsigned char* buffer, int buflen, bool& shutdown, unsigned long long IOtimestamp);

//Socket clients
typedef void (*GENERALERROR_EVENT)  (void* contextP, int errnum, std::string msg, bool& shutdown);
typedef void (*CONNECT_EVENT)       (void* contextP, unsigned char* data, int dataLen);
typedef void (*RX_EVENT)            (void* contextP, std::string ip, int port, unsigned char* buffer, int buflen, bool& shutdown, unsigned long long IOtimestamp);
typedef void (*RX_EVENT_GEN_BUF)    (void* contextP, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);
typedef void (*TX_EVENT)            (void* contextP, unsigned char* buffer, int buflen, bool& shutdown, unsigned long long IOtimestamp);

//IO Pools
#define DEFAULT_IO_RCV_POOL_SIZE            10
#define DEFAULT_IO_RCV_POOL_BUFFER_SIZE     64000
#define DEFAULT_IO_SND_POOL_SIZE            10
#define DEFAULT_IO_SND_POOL_BUFFER_SIZE     64000

#define SOCKET_IO_BUF_SIZE 1048576
