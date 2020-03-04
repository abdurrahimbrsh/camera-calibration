#pragma once

using namespace std;

#include <list>
#include <string>
#include "SRTUtils.h"
#include "GenericBuffer.h"
#include "ThreadSafe.h"

typedef enum
{
	VDT_NONE = 0,
	VDT_FFMPEG_H264 = 1,
	VDT_FFMPEG_MJPEG = 2,
	VDT_CUDA_H264 = 3,
	VDT_CUDA_MJPEG = 4
} VIDEO_DECODER_TYPE;

typedef enum
{
	VDOT_NONE = 0,
	VDOT_RGB = 1,
	VDOT_YUV420 = 2
} VIDEO_DECODER_OUTPUT_TYPE;

class CVideoDecoder
{
protected:
	CVideoDecoder(void);
public:
	virtual ~CVideoDecoder(void) {};
	void Init(void);

	void						Clear							();

	virtual bool				DecodeImage						(double& timeToDecodeMS, bool& decodeError, std::string& decodeErrorMsg) = 0;

	unsigned long long			GetCameraTimestamp				()											{ return m_cameraTimestamp; };
	CGenericBuffer*				GetDecodedImageDataBuffer		()											{ return m_pDecodedImageBuf; };
	VIDEO_DECODER_TYPE			GetDecoderType					()											{ return m_decoderType; };
	std::string					GetDecoderTypeAsString			();
	unsigned long long			GetDecodeTimestamp				()											{ return m_decodeTimestamp; };
	int							GetHeight						()											{ return m_imageHeight; };
	int							GetImageNumChannels				()											{ return m_imageNumChannels; };
	unsigned long long			GetNTPTimestampFromCamera		()											{ return m_ntpTimestamp; };
	unsigned int        		GetRTPTimestampFromCamera		()											{ return m_rtpTimestamp; }
	int							GetWidth						()											{ return m_imageWidth; };
	
	void						SetCameraTimestamp				(unsigned long long camTime) 				{ m_cameraTimestamp = camTime; };
	void						SetDecodedImageDataBuffer		(CGenericBuffer* decodedImageDataBuffer);
	void						SetDecoderType					(VIDEO_DECODER_TYPE decoderType) 			{ m_decoderType = decoderType; };
	void						SetDecodeTimeStamp				(unsigned long long decodeTime)   			{ m_decodeTimestamp = decodeTime; };
	void						SetFrameDimensions				(int width, int height, int numChannels);
	void						SetNTPTimestampFromCamera		(unsigned long long ntpTime) 				{ m_ntpTimestamp = ntpTime; };
	void						SetOutputType					(VIDEO_DECODER_OUTPUT_TYPE val)				{ m_outputType = val; };
	void						SetRTPTimestampFromCamera		(unsigned int rtpTime) 						{ m_rtpTimestamp = rtpTime; }
	void						SetRawImageData					(unsigned char* data, int dataLen);
	void						SignalResetDecoder				()											{ m_resetRequired.Set(true); };

	virtual void				Reset							() = 0;
	virtual void				ResetDecoder					() = 0;
	void						ResetIfRequired					();

protected:
	unsigned long long			m_cameraTimestamp;
	int							m_decodedImageDataLen;
	VIDEO_DECODER_TYPE			m_decoderType;
	unsigned long long			m_decodeTimestamp;
	int							m_imageHeight;
	int							m_imageNumChannels;
	int							m_imageWidth;
	unsigned long long			m_ntpTimestamp;
	VIDEO_DECODER_OUTPUT_TYPE	m_outputType;
	CGenericBuffer*				m_pDecodedImageBuf;	
	unsigned char*				m_rawImageData;
	int							m_rawImageDataLen;
	CThreadSafe<bool>			m_resetRequired;
	unsigned int				m_rtpTimestamp;
	pthread_mutex_t				m_videoDecoderSection;
};
