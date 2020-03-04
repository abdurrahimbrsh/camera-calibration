#pragma once

#include <set>
#include <list>
#include <string>
#include <pthread.h>

#include "RTPPacket_H264.h"
#include "JitterTracker.h"
#include "GenericCPUBuffer.h"
#include "SearidgeRAObjectPool.h"
#include "SPR_RollingAverage.h"

using namespace std;

typedef enum RTP_ERR
{
    RTP_BODY_INCOMG_DATA_TOO_LONG,
    RTP_BODY_BUFFER_SIZE_EXCEDED,
    RTP_400_BAD_REQ,
    RTP_401_AUTH,
    RTP_403_FORBIDDEN,
    RTP_404_NOT_FOUND,
    RTP_BODY_START_TOKEN_UNFOUND,
    RTP_BODY_INVALID_HEADER,
    RTP_BODY_MSG_TOO_LONG,
    RTP_BODY_END_TOKEN_UNFOUND,
    RTP_INVALID_CONTENT,
    RTP_NO_BOUNDARY
} RTSP_ERR;

typedef struct
{
    std::list<CRTPPacket_H264*> packetList;
    unsigned int frameTStamp;
    unsigned long long ioTStamp;
    bool startbit;
    bool endbit;
    bool gotA28;
    bool fullFrame;
    bool flushBuffer;
    unsigned int curSeqNumber;
    long long assemblyStartTick;
    bool isIFrame;

} FramePacketList;

static const int MAX_RTP_BUFSIZE		= 2000000;
static const int H_264_RTP_HEADER_SIZE		= 12;
static const int FIRST_TWO_BYTES		= 2;
static const int FU_INDICATOR_SIZE		= 1;
static const int FU_HEADER_SIZE			= 1;
static const int NAL_DELIMITER_SIZE		= 4;
static const int BOSCH_RTP_TS_FREQUENCY		= 90000; //90,000 Hz
static const int MAX_PACKET_DELAY		= 2;
static const int MAX_PACKET_QUEUE_SIZE		= 1000;

struct CH264_Packet_Comparator
{
    bool operator()(const CRTPPacket_H264* lhs, const CRTPPacket_H264* rhs);
};

typedef multiset<CRTPPacket_H264*, CH264_Packet_Comparator> h264Multiset_T;

class CRTPPacketQueue
{
public:
	CRTPPacketQueue();
	~CRTPPacketQueue();

	void				ClearVideoQueue();

	double				GetAvgJitter();
	//unsigned int                    GetBadFrameCount() { return m_badFrameCount.GetCount(); };
	unsigned char*                  GetFrameData();
	//unsigned int                    GetGoodFrameCount() { return m_goodFrameCount.GetCount(); };
	bool				GetFullFrameFromQueue(bool& isIFrame, unsigned long long& camTS, unsigned long long& ioTS, double& assemblyTimeMS, string& error);
	unsigned int                    GetFrameSize();
        
        double                          GetBufferFlushedCount(){return m_bufferFlushedCount.GetCount();};
        double                          GetIFrameBandwidth(){return m_iFrameBandwidth.GetAverage();};
        long long                       GetLastIFrameTS(){return m_lastIFrameTS.Get();};
        long long                       GetLastSPSRecvTS(){return m_lastSPSRecvTS.Get();};
        long long                       GetLastPPSRecvTS(){return m_lastPPSRecvTS.Get();};
        long long                       GetLastStartEndBitRecvTS(){return m_lastStartEndBitRecvTS.Get();};
        long long                       GetLastBufferFlushTS(){return m_lastBufferFlushTS.Get();};
        
        
	void				Init();
	
	bool				ParseRTPMessageAndEnqueue(CGenericCPUBuffer* buf, bool& fullFrame, unsigned long long IOtimestamp);

	void				ResetVideo();
        
        void                            SetMaxTimeInRTPQueue(int maxTimeInRTPQueue) {m_maxTimeInRTPQueue = maxTimeInRTPQueue;};
        
	void				ClearMessage();
        
        long long                       GetLastTimeWeGotFullFrame() {return m_lastTimeWeGotFullFrame;};

private:

        bool				AddPacketToVideoQueue(CGenericCPUBuffer* buf, unsigned int cameraTimestamp, unsigned long long IOtimestamp, unsigned int seq, int fragment_type, unsigned int ssrcIdent, bool isIFrame, bool startBit = false, bool endBit = false);

	void				FlushBuffer();

	void				GetStartAndEndBitFromA_28(unsigned char* data, unsigned int dataLen, bool& startBit, bool& endBit);
        
        bool                            IsIFrame(unsigned char* data, unsigned int dataLen);

	bool				WritePacketToFrame(CGenericCPUBuffer* buf, int fragment_type, bool startBit, bool endBit);

	CJitterTracker					m_jitterTracker;
	long long					m_lastTimeWeGotFullFrame;
	unsigned char					m_NAL_delimiter[NAL_DELIMITER_SIZE];
	h264Multiset_T					m_videoQueue;
	unsigned char*					m_frameBytes;
	unsigned int					m_currentSize;
	unsigned int					m_lastParsedTStamp;
	FramePacketList					m_framePacketList;
	CThreadSafe<bool>				m_waitForFirstIFrame;
	CThreadSafe<bool>                               m_needsResetVideo;
	CSearidgeRAObjectPool<CRTPPacket_H264>		m_videoPktRAPool;
	pthread_mutex_t                                 m_videoQueueMutex;
	//CSimplePerformanceRecordTS			m_goodFrameCount;
	//CSimplePerformanceRecordTS			m_badFrameCount;
        int                                             m_needSPS;
        int                                             m_needPPS;
        int                                             m_maxTimeInRTPQueue;
	int						m_lastSeqNo;
	CThreadSafe<bool>               		m_isSeqNoMax;
	CThreadSafe<bool>				m_resetSeqNo;
        
        CSPR_RollingAverage                             m_bufferFlushedCount;
        CSPR_RollingAverage                             m_iFrameBandwidth;
        CThreadSafe<long long>                          m_lastIFrameTS;
        CThreadSafe<long long>                          m_lastSPSRecvTS;
        CThreadSafe<long long>                          m_lastPPSRecvTS;
        CThreadSafe<long long>                          m_lastStartEndBitRecvTS;
        CThreadSafe<long long>                          m_lastBufferFlushTS;

        
};

