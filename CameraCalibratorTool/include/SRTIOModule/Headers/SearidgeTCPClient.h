#pragma once

#include "SRTIOModule.h"
#include "ThreadSafe.h"

#include <string>

class CSearidgeTCPClient : public CSRTIOModule
{
public:
    CSearidgeTCPClient();
    ~CSearidgeTCPClient();

    IO_STATE					GetState		();

    bool						Start			(std::string& errorMessage);

    bool 						SendAsync		(std::string msg);
    void 						Stop			();

private:
    static void*    			ConnectThread   (void* data);
    
    static bool     			InitSocket      (int& sock);
   
    CThreadSafe<pthread_t>		m_connectThreadHandle;
    CThreadSafe<bool>           m_connectThreadCompleted;
};
