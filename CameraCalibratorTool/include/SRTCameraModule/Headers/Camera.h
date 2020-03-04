#pragma once

#include <map>
#include "CameraConfig.h"
#include "ThreadSafe.h"
#include "CameraDataConnection.h"
#include "SPR_RollingAverage.h"
#include "SearidgeResourcePool.h"
#include "VideoDecoder.h"

#define CAMERA_CONNECTION_LIMITS_MSEC		5000

typedef enum CAM_STATUS
{
	CAMSTATUS_OK,
	CAMSTATUS_DISCONNECTED,
	CAMSTATUS_STOPPED,
	CAMSTATUS_STALED,
	CAMSTATUS_CONNECTING,
	CAMSTATUS_ERROR
}CAM_STATUS;

static const int SNMP_UPDATE_RATE_MS = 5000;

class CCamera
{
public:

    struct camera_videoCallbacks
    {
        void* contextPtr;
        ON_FRAME_EVENT frameProc;
        CAMERA_DISCONNECT_EVENT cameraDCProc;
    };

protected:
    CCamera();

public:
    virtual ~CCamera(void);

    //functions:
    void		                AddVideoCallbacks               (void* contextPtr, ON_FRAME_EVENT proc, CAMERA_DISCONNECT_EVENT dcProc);

    CAM_STATUS		            GetCamStatus		            ();
    CCameraConfig		        GetConfig			            ()	{ return m_config; };
    int				            GetID				            ()	{ return m_config.GetId(); };
    unsigned long long		    GetLastFrameTStamp		        ()	{ return m_lastFrameTStamp; };

    bool			            IsCameraStaled			        (long long& diffMsec);
    bool			            IsStarted			            ()	{return m_isStarted;};

    void			            RemoveVideoCallback             (void* contextPtr, ON_FRAME_EVENT proc, CAMERA_DISCONNECT_EVENT dcProc);

    void		                SetConfig			            (CCameraConfig config) { m_config = config; };
    virtual void		        Start				            () = 0;
    virtual void		        Stop				            () = 0;

    virtual void		        Tick				            ()	= 0;
    //void                        UpdateSnmpMetric                (vector<oid> v);

protected:
    void                        InitVideoDecoder                ();
    bool			            IsDigestAutenticationReq        (unsigned char* data, bool isVideoAuth = true);

    static void                 OnVideoUDPIOError		        (void* contextP, int errnum, std::string msg, bool& shutdown);
    static void                 OnVideoUDPIORxGenBuf			(void* contextP, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);
    static void                 OnVideoUDPIOTxComplete		    (void* contextP, unsigned char* buffer, int buflen, bool& shutdown, unsigned long long IOtimestamp);
    static void                 OnVideoTcpClientConnect		    (void* contextP, unsigned char* data, int dataLen);
    static void                 OnVideoTcpClientError		    (void* contextP, int errnum, std::string msg, bool& shutdown);
    static void                 OnVideoTcpClientRxGenBuf        (void* contextP, std::string ip, int port, CGenericCPUBuffer* buf, bool& shutdown, unsigned long long IOtimestamp);

    virtual bool			    ProcessIncomingVideoData	    (std::string ip, int port, CGenericCPUBuffer* buf, unsigned long long IOtimestamp) = 0;
    void			            ProcessFullImage		        (unsigned char* data, unsigned int dataLen, unsigned long long camTimestamp, unsigned long long ioTimestamp, bool isIFrame);

    virtual void                UpdateSNMPTick                  ();
    
    //General
    CCameraDataConnection*                  m_cameraDataConnection;
    CCameraConfig                           m_config;
    CSearidgeResourcePool<CGenericBuffer>   m_decodedImagePool;
    pthread_mutex_t                         m_decodedImagePoolSection;
    bool                                    m_isStarted;
    CThreadSafe<long long>                  m_lastConnectionAttemptTick;
    CThreadSafe<long long>                  m_lastCompleteImageTime;
    unsigned long long                      m_lastFrameTStamp;
    CThreadSafe<long long>                  m_lastUpdateTime;
    CThreadSafe<long long>                  m_lastUpdateToSnmpMgr;
    std::map<void*, camera_videoCallbacks>  m_videoCallbackList;
    pthread_mutex_t                         m_videoCallbackListSection;
    CVideoDecoder*                          m_pVideoDecoder;
    
    // Performance Records
    CSPR_RollingAverage                     m_udpBandwidth;
    CSPR_RollingAverage                     m_tcpBandwidth;
    CSPR_RollingAverage                     m_incFPS;
    CSPR_RollingAverage                     m_propagatingTime;
    CSPR_RollingAverage                     m_staleCount;
};