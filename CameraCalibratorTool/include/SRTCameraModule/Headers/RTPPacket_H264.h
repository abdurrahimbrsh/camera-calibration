#pragma once

#include "GenericCPUBuffer.h"

#define H264_RTP_PACKET_BUFFER_DEFAULT_SIZE	1500

class CRTPPacket_H264
{
public:
	CRTPPacket_H264(void* objectConstructorArg);
	~CRTPPacket_H264();

	void 		Clear				();

	bool 		GetIsInUse			();

	void 		Set					(CGenericCPUBuffer* buf, unsigned int cameraTimestamp, unsigned long long IOtimestamp, unsigned int seq, int fragType, unsigned int ssrcIdent, bool isIFrame, bool startBit, bool endBit);
	void 		SetIsInUse			(bool inUse);

	CGenericCPUBuffer*				m_buf;
	unsigned int					m_camTimestamp;
	bool							m_endBit;
	int                             m_fragementType;
	bool							m_inUse;
	unsigned long long              m_ioTimestamp;
	bool                        	m_isIFrame;
	long long                       m_localTimestamp;
	unsigned int					m_seqNum;
	unsigned int					m_ssrcIdent;
	bool							m_startBit;
};