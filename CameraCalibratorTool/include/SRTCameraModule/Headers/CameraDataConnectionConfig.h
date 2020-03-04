#pragma once

#include <string>

#include "SocketDefs.h"

class CCameraDataConnectionConfig
{
public:

    CCameraDataConnectionConfig(void);
    ~CCameraDataConnectionConfig(void);

    std::string		    GetPassword                     ()	                        { return m_password; };
    bool		        GetRtspConnectionMaster         ()	                        { return m_rtspConnectionMaster; };
    std::string		    GetRTSPUrl                      ()	                        { return m_rtspUrl; };
    std::string		    GetUser                         ()	                        { return m_user; };
    std::string			GetLocalIP					    () 	                        { return m_localIP; };
	int					GetLocalPort				    () 	                        { return m_localPort; };
	std::string 		GetMulticastIP				    () 	                        { return m_multicastIP; };
	int 				GetMulticastPort			    () 	                        { return m_multicastPort; };
	std::string			GetRemoteIP					    () 	                        { return m_remoteIP; };
	int					GetRemotePort				    () 	                        { return m_remotePort; };
    int 				GetReceivePoolBufferSize	    () 	                        { return m_receivePoolBufferSize; };
	int 				GetReceivePoolSize			    () 	                        { return m_receivePoolSize; };
    void* 				SetVideoCallerContextPtr		() 				            { return m_videoCallerContextPtr; };
    CONNECT_EVENT 	    GetVideoTCPClientConnectProcPtr () 		                    { return m_videoTCPClientConnectProcPtr; };
    GENERALERROR_EVENT 	GetVideoTCPClientErrorProcPtr	()                          { return m_videoTCPClientErrorProcPtr; };
    RX_EVENT_GEN_BUF 	GetVideoTCPClientRxProcPtr	    () 		                    { return m_videoTCPClientRxProcPtr; };
    GENERALERROR_EVENT 	GetVideoUDPIOErrorProcPtr		() 	                        { return m_videoUDPIOErrorProcPtr; };
    RX_EVENT_GEN_BUF 	GetVideoUDPIORxProcPtr			() 		                    { return m_videoUDPIORxProcPtr; };
    TX_EVENT 			GetVideoUDPIOTxProcPtr			() 	                        { return m_videoUDPIOTxProcPtr; };
    
    void		        SetPassword                     (std::string val)           { m_password = val; };
    void		        SetRtspConnectionMaster         (bool val)                  { m_rtspConnectionMaster = val; };
    void		        SetRTSPUrl                      (std::string val)           { m_rtspUrl = val; };
    void		        SetUser                         (std::string val)           { m_user = val; };
    void				SetLocalIP					    (std::string val) 		    { m_localIP = val; };
	void				SetLocalPort				    (int val) 				    { m_localPort = val; };
	void 				SetMulticastIP				    (std::string val) 		    { m_multicastIP = val; };
	void 				SetMulticastPort			    (int val) 				    { m_multicastPort = val; };
	void				SetRemoteIP					    (std::string val) 		    { m_remoteIP = val; };
	void				SetRemotePort				    (int val) 				    { m_remotePort = val; };
    void 				SetReceivePoolBufferSize	    (int val) 				    { m_receivePoolBufferSize = val; };
	void 				SetReceivePoolSize			    (int val) 				    { m_receivePoolSize = val; };
    void 				SetVideoCallerContextPtr		(void* val) 				{ m_videoCallerContextPtr = val; };
    void 				SetVideoTCPClientConnectProcPtr (CONNECT_EVENT val) 		{ m_videoTCPClientConnectProcPtr = val; };
    void 				SetVideoTCPClientErrorProcPtr	(GENERALERROR_EVENT val)    { m_videoTCPClientErrorProcPtr = val; };
    void 				SetVideoTCPClientRxProcPtr	    (RX_EVENT_GEN_BUF val) 		{ m_videoTCPClientRxProcPtr = val; };
    void 				SetVideoUDPIOErrorProcPtr		(GENERALERROR_EVENT val) 	{ m_videoUDPIOErrorProcPtr = val; };
    void 				SetVideoUDPIORxProcPtr			(RX_EVENT_GEN_BUF val) 		{ m_videoUDPIORxProcPtr = val; };
    void 				SetVideoUDPIOTxProcPtr			(TX_EVENT val) 	            { m_videoUDPIOTxProcPtr = val; };


    void Clear	()
    {
        m_id                            = -1;
        m_password                      = "";
        m_rtspConnectionMaster          = false;
        m_rtspUrl                       = "";
        m_user                          = "";
        m_localIP                       = "";
	    m_localPort                     = -1;
        m_multicastIP                   = "";
	    m_multicastPort                 = -1;
	    m_remoteIP                      = "";
	    m_remotePort                    = -1;
        m_receivePoolBufferSize         = -1;
	    m_receivePoolSize               = -1;
        m_videoCallerContextPtr         = NULL;
        m_videoTCPClientConnectProcPtr  = NULL;
        m_videoTCPClientErrorProcPtr    = NULL;
        m_videoTCPClientRxProcPtr       = NULL;
        m_videoUDPIOErrorProcPtr        = NULL;
        m_videoUDPIORxProcPtr           = NULL;
        m_videoUDPIOTxProcPtr           = NULL;
   };

    CCameraDataConnectionConfig& operator =(const CCameraDataConnectionConfig& rhs)
    {
        if(this != &rhs)
        {
            this->m_id                              = rhs.m_id;
            this->m_password                        = rhs.m_password;
            this->m_rtspConnectionMaster            = rhs.m_rtspConnectionMaster;
            this->m_rtspUrl                         = rhs.m_rtspUrl;
            this->m_user                            = rhs.m_user;
            this->m_localIP                         = rhs.m_localIP;
	        this->m_localPort                       = rhs.m_localPort;
            this->m_multicastIP                     = rhs.m_multicastIP;
	        this->m_multicastPort                   = rhs.m_multicastPort;
	        this->m_remoteIP                        = rhs.m_remoteIP;
	        this->m_remotePort                      = rhs.m_remotePort;
            this->m_receivePoolBufferSize           = rhs.m_receivePoolBufferSize;
	        this->m_receivePoolSize                 = rhs.m_receivePoolSize;
            this->m_videoCallerContextPtr           = rhs.m_videoCallerContextPtr;
            this->m_videoTCPClientConnectProcPtr    = rhs.m_videoTCPClientConnectProcPtr;
            this->m_videoTCPClientErrorProcPtr      = rhs.m_videoTCPClientErrorProcPtr;
            this->m_videoTCPClientRxProcPtr         = rhs.m_videoTCPClientRxProcPtr;
            this->m_videoUDPIOErrorProcPtr          = rhs.m_videoUDPIOErrorProcPtr;
            this->m_videoUDPIORxProcPtr             = rhs.m_videoUDPIORxProcPtr;
            this->m_videoUDPIOTxProcPtr             = rhs.m_videoUDPIOTxProcPtr;
        }

        return *this;
    };

private:
    //Camera Parameters
    int                 m_id;
    std::string		    m_password;
    bool		        m_rtspConnectionMaster;
    std::string         m_rtspUrl;
    std::string		    m_user;

    //IO Connection Parameters
    std::string			m_localIP;
	int					m_localPort;
    std::string 		m_multicastIP;
	int 				m_multicastPort;
	std::string			m_remoteIP;
	int					m_remotePort;
    int 				m_receivePoolBufferSize;
	int 				m_receivePoolSize;

    //IO Callbacks
    void*               m_videoCallerContextPtr;
    CONNECT_EVENT       m_videoTCPClientConnectProcPtr;
    GENERALERROR_EVENT  m_videoTCPClientErrorProcPtr;
    RX_EVENT_GEN_BUF    m_videoTCPClientRxProcPtr;
    GENERALERROR_EVENT  m_videoUDPIOErrorProcPtr;
    RX_EVENT_GEN_BUF    m_videoUDPIORxProcPtr;
    TX_EVENT            m_videoUDPIOTxProcPtr; 
};