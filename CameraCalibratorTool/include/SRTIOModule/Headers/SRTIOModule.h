#pragma once

#include "SocketDefs.h"
#include "SRTIOModuleConfig.h"
#include "SearidgeOpenSocket.h"
#include "SearidgeSmartPtr.h"
#include "GenericBuffer.h"

#include <string>

typedef void (*CAMERA_DISCONNECT_EVENT)     (void* context, int camID);
typedef void (*ON_FRAME_EVENT)              (void* context, void* camPtr, CSearidgeSmartPtr<CGenericBuffer>* dataPtr);
typedef void (*ON_CAM_DISC)                 (void* context);

class CSRTIOModule
{
public:
	CSRTIOModule();
	virtual ~CSRTIOModule();

	virtual IO_STATE	GetState		() = 0;

	virtual bool		Start			(std::string& errorMessage) = 0;
    bool				IsStarted		()								{ return m_socket.GetState() == SS_ACTIVATED; };

	void				SetConfig		(CSRTIOModuleConfig config)		{ m_config = config; };
	virtual void 		Stop			() = 0;

protected:
    static void     	OnDataRx        (void* socketP, void* context, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);
    static void     	OnDataTx        (void* socketP, void* context, unsigned char* data, int dataLen, bool& shutdown, unsigned long long IOtimestamp);
    static void     	OnDisconnect    (void* socketP, void* context);
    static void     	OnError         (void* socketP, void* context, int errnum, char* msg, bool& shutdown);

	CSRTIOModuleConfig	m_config;

    CThreadSafe<bool>	m_multicastSetSockFailed;

	CSearidgeOpenSocket	m_socket;
    
private:

};
