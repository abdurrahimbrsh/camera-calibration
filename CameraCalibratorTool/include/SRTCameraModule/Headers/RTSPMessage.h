#pragma once
#include "SearidgeSimpleMessage.h"

//RTSP Messages
#define CONTENT_TYPE_RTSP           "application/sdp\0"
#define BOSCH_RTSP                                          "RTSP/1.0\0"
#define RTSP					"RTSP/1.0\0"
#define RTSP_200_OK				"RTSP/1.0 200 OK\0"
#define RTSP_GET_PARAMETER              "GET_PARAMETER "
#define RTSP_DESCRIBE				"DESCRIBE "
#define RTSP_SETUP				"SETUP "
#define RTSP_PLAY				"PLAY "
#define RTSP_OPTIONS				"OPTIONS "
#define RTSP_TEARDOWN				"TEARDOWN "
#define RTSP_CSEQ				"CSeq: "
#define RTSP_SESSION				"Session: "
#define RTSP_SESSION_END 			"; timeout"
#define RTSP_SESSION_END_BOSCH 			";timeout"
#define RTSP_SPSANDPPS_BOSCH 			"sprop-parameter-sets="
#define END_LEN 				4
//cameras were found to have a stream timeout of 60 seconds. We send 4 "keep-alive" messages in the form of OPTION messages per minute.
#define NUM_SECONDS_RTSP_INTERVAL_MSEC                      15000

#define RTSP_ERR_MSG_BODY_INCOMG_DATA_TOO_LONG	"%s: Incoming data is too big for buffer"
#define RTSP_ERR_MSG_BODY_BUFFER_SIZE_EXCEDED	"%s: Buffer size Exceeded limit"
#define RTSP_ERR_MSG_400_BAD_REQ		"%s: 400 Bad Request"
#define RTSP_ERR_MSG_401_AUTH			"%s: 401 Unauthorized, verify credentials"
#define RTSP_ERR_MSG_403_FORBIDDEN		"%s: 403 Forbidden"
#define RTSP_ERR_MSG_404_NOT_FOUND		"%s: 404 Not found"
#define RTSP_ERR_MSG_BODY_START_TOKEN_UNFOUND	"%s: Start token was not found"
#define RTSP_ERR_MSG_BODY_INVALID_HEADER	"%s: Header is corrupted"
#define RTSP_ERR_MSG_BODY_MSG_TOO_LONG		"%s: Message is too long for buffer"
#define RTSP_ERR_MSG_BODY_END_TOKEN_UNFOUND	"%s: End token not found"
#define RTSP_ERR_MSG_INVALID_CONTENT		"%s: Invalid content type"
#define RTSP_ERR_MSG_RTSP_NO_BOUNDARY		"%s: Could not find boundary section"
#define RTSP_ERR_MSG_DEFAULT			"%s: Undefined error"

#define RTP_HEADER_SIZE				12
#define RTSP_OPTIONS_CSEQ			2
#define RTSP_SETUP_CSEQ				4
#define RTSP_DESCRIBE_CSEQ			3
#define RTSP_TEARDOWN_CSEQ			7
#define RTSP_PLAY_CSEQ				6

class CRTSPMessage : 
    public CSearidgeSimpleMessage
{
public:
	CRTSPMessage(void);
	~CRTSPMessage(void);

	int                             AddDataUntilYouAreFull	(unsigned char* dataIn, int len);
	void                            Clear();
	std::string                     GetCameraClassName()    { return m_cameraClassName; };
	unsigned char*			GetStartToken()         { return m_startToken; };
	int				GetStartTokenLen()      { return (int)m_startTokenLen; };
	unsigned char*			GetEndToken()           { return m_endToken; };
	int				GetEndTokenLen()        { return (int)m_endTokenLen; };
	unsigned char*			GetHeaderEndToken()     { return m_headerEndToken; };
	int				GetHeaderEndTokenLen()  { return (int)m_headerEndTokenLen; };
	std::string			GetSessionID()          { return m_sessionID; };
	std::string			GetSPSandPPS()          { return m_SPSandPPS; };
	int				GetCSeq()               { return m_cSeq; };
	std::string			GetLastErrorMsg();

	void                            Init(std::string& contentType)                  { m_strContentType = contentType; };
	void                            SetCameraClassName(std::string cameraClassName) { m_cameraClassName = cameraClassName; };

private:
	unsigned char*			m_headerEndToken;
        unsigned int                    m_headerEndTokenLen;
	unsigned char*			m_header;
        unsigned int                    m_headerLen;
	unsigned char                   m_end[END_LEN];
	std::string			m_strContentType;
	std::string			m_sessionID;
	std::string			m_SPSandPPS;
	int				m_cSeq;
	// m_cameraClassName variable will initialize from any class which will be inherited from CCamera_H264_Base
	std::string			m_cameraClassName;

	typedef enum RTSP_ERR
	{
		RTSP_BODY_INCOMG_DATA_TOO_LONG,
		RTSP_BODY_BUFFER_SIZE_EXCEDED,
		RTSP_400_BAD_REQ,
		RTSP_401_AUTH,
		RTSP_403_FORBIDDEN,
		RTSP_404_NOT_FOUND,
		RTSP_BODY_START_TOKEN_UNFOUND,
		RTSP_BODY_INVALID_HEADER,
		RTSP_BODY_MSG_TOO_LONG,
		RTSP_BODY_END_TOKEN_UNFOUND,
		RTSP_INVALID_CONTENT,
		RTSP_NO_BOUNDARY
	} RTSP_ERR;


};


