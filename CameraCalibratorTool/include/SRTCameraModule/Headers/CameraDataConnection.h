#pragma once
#include <string>

#include "CameraDataConnectionConfig.h"
#include "SearidgeTCPClient.h"
#include "SearidgeUDPIO.h"

typedef enum
{
	CDC_CONNECTING,
	CDC_CONNECTED,
	CDC_DISCONNECTED
} CAMERA_DATA_CONNECTION_STATE;

class CCameraDataConnection
{
public:
    
    CCameraDataConnection(void);
    virtual ~CCameraDataConnection(void);

    void                                    ClearMD5AuthenticationData          ();

    std::string                             GetFormattedAuthenticationResponse  (bool isDigestAuthenticationReq);
    std::string                             GetFormattedResponse                ();
    std::string                             GetNonceVideo                       ()                                          { return m_nonce; };
    std::string                             GetRealmVideo                       ()                                          { return m_realm; };
    virtual CAMERA_DATA_CONNECTION_STATE    GetState                            () = 0;

    void                                    SetAuthenticationRequest            (std::string &request);
    virtual bool                            Start                               (std::string& errorMessage) = 0;
    virtual void                            Stop		                        () = 0;
    
    void				                    SetConfig		                    (CCameraDataConnectionConfig config)		{ m_config = config; };
    void                                    SetNonce                            (std::string nonce)                         { m_nonce = nonce; };
    void                                    SetRealm                            (std::string realm)                         { m_realm = realm; };

protected:
    static void                             OnVideoTcpClientConnect             (void* context, unsigned char* data, int dataLen);
    static void                             OnVideoTcpClientError               (void* context, int errnum, std::string msg, bool& shutdown);
    static void                             OnVideoTcpClientRecv                (void* context, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);
    static void                             OnVideoUdpIOError                   (void* context, int errnum, std::string msg, bool& shutdown);
    static void                             OnVideoUdpIORecv                    (void* context, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);
    static void                             OnVideoUdpIOTxComplete              (void* context, unsigned char* data, int dataLen, bool& shutdown, unsigned long long IOtimestamp);

    CCameraDataConnectionConfig             m_config;

    CSearidgeTCPClient                      m_videoTcpClient;
    CSearidgeUDPIO                          m_videoUDPIO;

    std::string                             m_nonce;
    std::string                             m_realm;
};