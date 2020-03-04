#pragma once

#include "CameraDataConnection.h"

#define RTP_HEADER_SIZE             12
#define RTSP_USER                   "Searidge RTSP User"
#define RTSP_OPTIONS_CSEQ           2
#define RTSP_SETUP_CSEQ             4
#define RTSP_DESCRIBE_CSEQ          3
#define RTSP_TEARDOWN_CSEQ          7
#define RTSP_PLAY_CSEQ              6
#define RTSP_GET_PARAMETER_CSEQ     6

typedef enum
{
	DISCONNECTED	= 0,
	READY_TO_SETUP	= 1,
	SETUP_SENT	    = 2,
	READY_TO_PLAY	= 3,
	PLAY_SENT	    = 4,
	CONNECTED	    = 5,
	TEARDOWN	    = 6
} RTSP_CONNECTION_SEQUENCE;

class CCameraDataConnection_RTSP : public CCameraDataConnection
{
public:

    CCameraDataConnection_RTSP();
    ~CCameraDataConnection_RTSP();

    CAMERA_DATA_CONNECTION_STATE    GetState                            ();

    bool                            Start                               (std::string& errorMessage);
    void                            Stop                                ();
    
    bool                            SendVideoDescribeRequest            ();
    bool                            SendVideoGetParameterRequest        ();
    bool                            SendVideoOptionsRequest             ();
    bool                            SendVideoPlayRequest                ();
    bool                            SendVideoSetupRequest               ();
    bool                            SendVideoTearDownRequest            ();
    void                            SetVideoSessionID                   (std::string id);
    
private:
    std::string                     m_videoSessionID;
};
