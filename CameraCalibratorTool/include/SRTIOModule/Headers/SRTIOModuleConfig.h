#pragma once

#include "SocketDefs.h"
#include "ThreadSafe.h"

#include <string>

class CSRTIOModuleConfig
{
public:
	CSRTIOModuleConfig();
	~CSRTIOModuleConfig();

	void				Clear						();

	int        			GetConnectionTimeout		() 							{ return m_connectionTimeout; };
	std::string			GetLocalIP					() 							{ return m_localIP; };
	int					GetLocalPort				() 							{ return m_localPort; };
	std::string 		GetMulticastIP				() 							{ return m_multicastIP; };
	int 				GetMulticastPort			() 							{ return m_multicastPort; };
	std::string			GetRemoteIP					() 							{ return m_remoteIP; };
	int					GetRemotePort				() 							{ return m_remotePort; };
	IOModuleType 		GetType						() 							{ return m_type; };

	int 				GetReceivePoolBufferSize	() 							{ return m_receivePoolBufferSize; };
	int 				GetReceivePoolSize			() 							{ return m_receivePoolSize; };
	int 				GetSendPoolBufferSize		() 							{ return m_sendPoolBufferSize; };
	int 				GetSendPoolSize				() 							{ return m_sendPoolSize; };

	void* 				GetCallerContextPtr			() 							{ return m_callerContextPtr; };
	CONNECT_EVENT   	GetConnectProcPtr			() 							{ return m_connectProcPtr; };
	GENERALERROR_EVENT	GetGeneralErrorProcPtr		() 							{ return m_generalErrorProcPtr; };
	RX_EVENT_GEN_BUF 	GetRxGenBufProcPtr			() 							{ return m_rxGenBufProcPtr; };
	RX_EVENT 			GetRxProcPtr				() 							{ return m_rxProcPtr; };
	TX_EVENT 			GetTxProcPtr				() 							{ return m_txProcPtr; };

	void        		SetConnectionTimeout		(int val) 					{ m_connectionTimeout = val; };
	void				SetLocalIP					(std::string val) 			{ m_localIP = val; };
	void				SetLocalPort				(int val) 					{ m_localPort = val; };
	void 				SetMulticastIP				(std::string val) 			{ m_multicastIP = val; };
	void 				SetMulticastPort			(int val) 					{ m_multicastPort = val; };
	void				SetRemoteIP					(std::string val) 			{ m_remoteIP = val; };
	void				SetRemotePort				(int val) 					{ m_remotePort = val; };
	void 				SetType						(IOModuleType val) 			{ m_type = val; };

	void 				SetReceivePoolBufferSize	(int val) 					{ m_receivePoolBufferSize = val; };
	void 				SetReceivePoolSize			(int val) 					{ m_receivePoolSize = val; };
	void 				SetSendPoolBufferSize		(int val) 					{  m_sendPoolBufferSize = val; };
	void 				SetSendPoolSize				(int val) 					{ m_sendPoolSize = val; };

	void 				SetCallerContextPtr			(void* val) 				{ m_callerContextPtr = val; };
	void				SetConnectProcPtr			(CONNECT_EVENT val) 		{ m_connectProcPtr = val; };
	void				SetGeneralErrorProcPtr		(GENERALERROR_EVENT val) 	{ m_generalErrorProcPtr = val; };
	void 				SetRxGenBufProcPtr			(RX_EVENT_GEN_BUF val) 		{ m_rxGenBufProcPtr = val; };
	void 				SetRxProcPtr				(RX_EVENT val) 				{ m_rxProcPtr = val; };
	void 				SetTxProcPtr				(TX_EVENT val) 				{ m_txProcPtr = val; };
    
private:
	//General
	int                 m_connectionTimeout;
	std::string			m_localIP;
	int					m_localPort;
	std::string 		m_multicastIP;
	int 				m_multicastPort;
	std::string			m_remoteIP;
	int					m_remotePort;
	IOModuleType 		m_type;

	//IO Pools
	int 				m_receivePoolBufferSize;
	int 				m_receivePoolSize;
	int 				m_sendPoolBufferSize;
	int 				m_sendPoolSize;

    //Callbacks
	void* 				m_callerContextPtr;
	CONNECT_EVENT       m_connectProcPtr;
	GENERALERROR_EVENT 	m_generalErrorProcPtr;
	RX_EVENT_GEN_BUF 	m_rxGenBufProcPtr;
	RX_EVENT 			m_rxProcPtr;
	TX_EVENT 			m_txProcPtr;
};
