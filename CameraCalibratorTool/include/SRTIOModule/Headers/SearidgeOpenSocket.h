#pragma once

/*** LINUX DESIGN NOTES
 * - This class header also contains all the Linux system headers for Berkeley 
 *   sockets stuff, since this file is included everywhere.
 */

#include "SocketDefs.h"
#include "ThreadSafe.h"
#include "SearidgeRAObjectPool.h"
#include "GenericCPUBuffer.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <list>
#include <pthread.h>

class CSearidgeOpenSocket
{
public:
	CSearidgeOpenSocket();
	~CSearidgeOpenSocket();

	bool 	Create				(int sd, std::string localIP, int localPort, std::string remoteIP, int remotePort, std::string multicastIP, int multicastPort,
								 void* callerContextP, RXIN_EVENT rxCallback, TXIN_EVENT txCallback, GERR_EVENT errCallback, SOCKET_TYPE type,
								 int receivePoolSize, int receivePoolBufferSize, int outputPoolSize, int outputPoolBufferSize);

    void 			Destroy		(std::string leaveMulticastGroupAddress, std::string leaveMulticastGroupReceiveAddress);

    SOCKET_STATUS 	GetState	();

    bool 			SendAsync	(const char* msg, unsigned int msglen, const char* ip = "", int port = 0);
    
private:
    void 			Clean		();

    static void* 	IOThread	(void* data);

    //General
    std::string									m_localIP;
    int											m_localPort;
    std::string 								m_multicastIP;
    int 										m_multicastPort;
    std::string									m_remoteIP;
    int											m_remotePort;
    int 										m_socket;
    SOCKET_TYPE 								m_socketType;
    CThreadSafe<bool> 							m_ioThreadCompleted;
  
    //IO Thread
    CThreadSafe<bool> 							m_isTimeToGo_IO;
    pthread_t         							m_IO_ThreadHandle;
    
    //Callbacks
    GERR_EVENT									m_errProcPtr;
    TXIN_EVENT       							m_txProcPtr;
    RXIN_EVENT          						m_rxProcPtr;
    void*               						m_callerContextP;
    
    // Send Queue
    std::list<void*> 							m_sendQueue;
    pthread_mutex_t 							m_sendQueueMutex;
    
    //Receive Object Pool
    CSearidgeRAObjectPool<CGenericCPUBuffer>	m_rcvObjectPool;
};
