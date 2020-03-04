#pragma once

#include <string>

#include "VideoDecoder.h"

//ffmpeg
extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavutil/opt.h>
	#include <libavutil/channel_layout.h>
	#include <libavutil/mathematics.h>
	#include <libavutil/imgutils.h>
	#include <libavutil/samplefmt.h>
	#include <libavutil/common.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>

	#ifndef NEW_GET_PIX
	#define NEW_GET_PIX

	#endif
}

class CVideoDecoder_FFMPEG : public CVideoDecoder
{
public:
	CVideoDecoder_FFMPEG(void);
	virtual ~CVideoDecoder_FFMPEG(void);

	bool						DecodeImage		(double& timeToDecodeMS, bool& decodeError, std::string& decodeErrorMsg);

	void						Reset			();
	void						ResetDecoder	();

private:
	void						CloseAV			();

	int							DecodePacket	(int& got_frame, int cached, double timeStamp, double copyTime, std::string& errorMsg);

	bool						InitDecFrame	();

	void						SetupAV			();

	AVPacket					m_avpkt;
	AVCodec*					m_codec;
	uint8_t**					m_dataArray;
	AVFrame*					m_decFrame;
	AVFrame*					m_frame;
	SwsContext*					m_modifContext;
	AVDictionary*				m_pAVOptionDictionary;
	AVCodecContext*				m_videoDecContext;
	int							m_videoStreamIndex;
};