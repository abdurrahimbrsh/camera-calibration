#pragma once

#include "GenericCPUBuffer.h"
#include "Camera.h"
#include "RTSPMessage.h"
#include "ThreadSafe.h"
#include "RTPPacketQueue.h"
#include "SPR_RollingAverage.h"
#include "CameraDataConnection_RTSP.h"

class CCamera_RTSP : public CCamera
{
public:
	CCamera_RTSP();
	~CCamera_RTSP();

	RTSP_CONNECTION_SEQUENCE    	GetVideoConnectionSeqPos        	()								{ return m_videoConnectionSeqPos.Get(); };

	void							SetVideoConnectionSeqPos        	(RTSP_CONNECTION_SEQUENCE seq) 	{ m_videoConnectionSeqPos.Set(seq); };
	void							Start								();
	void							Stop								();
	void							Tick								();
		
protected:

	//functions
	bool			    			ProcessIncomingVideoData	     	(std::string ip, int port, CGenericCPUBuffer* buf, unsigned long long IOtimestamp);
	bool							ProcessIncomingVideoTCPData			(CGenericCPUBuffer* buf);
	bool		        			ProcessIncomingVideoUDPData     	(CGenericCPUBuffer* buf, unsigned long long IOtimestamp);

	static void*                	RTSPCameraProcessThread             (void* lp);
    void			            	RTSPCameraProcessTick               ();

	bool                                    m_isTimeToGo_RTSPCameraProcess;
	CThreadSafe<long long>                  m_lastOptionsSent;
	CThreadSafe<bool>						m_needToSendDescribe;
	CRTPPacketQueue                         m_packetQueue;
	pthread_t                               m_rtspCameraProcessThreadHandle;
    CRTSPMessage							m_rtspMessage;
	CThreadSafe<RTSP_CONNECTION_SEQUENCE>   m_videoConnectionSeqPos;

	// Performance Records
	CSPR_RollingAverage                     m_rtspErrorCount;
    CThreadSafe<long long>                  m_lastRTSPErrorTS;   
    CThreadSafe<long long>                  m_lastRTSPDescribeResponseTS;
    CThreadSafe<long long>                  m_lastRTSPSetupResponseTS;
    CThreadSafe<long long>                  m_lastRTSPPlayResponseTS;
    CThreadSafe<long long>                  m_lastRTSPTeardownResponseTS;
    CThreadSafe<long long>                  m_lastRTSPOptionsResponseTS;
};
