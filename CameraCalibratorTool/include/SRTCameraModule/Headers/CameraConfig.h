#pragma once

#include <string>

#include "SRTUtils.h"
#include "VideoDecoder.h"

typedef enum CAM_TYPE
{
    CT_UNKNOWN = 0,
    CT_RTSP_H264 = 1
} CAM_TYPE;

class CCameraConfig
{
public:

    CCameraConfig(void);
    ~CCameraConfig(void);

    int			                GetDecodedImageBufferSize   ()	                            { return m_decodedImageBufferSize; };
    int			                GetDecodedImagePoolSize     ()	                            { return m_decodedImagePoolSize; };
    bool		                GetEnabled                  ()	                            { return m_enabled; };
    int			                GetFramerate                ()	                            { return m_framerate; };
    int			                GetId                       ()	                            { return m_id; };
    int			                GetImageHeight              ()	                            { return m_imageHeight; };
    int			                GetImageNumChannels         ()	                            { return m_imageNumChannels; };
    int			                GetImageWidth               ()	                            { return m_imageWidth; };
    int                         GetMaxTimeInRTPQueue        ()                              { return m_maxTimeInRTPQueue; };
    std::string		            GetPassword                 ()	                            { return m_password; };
    bool		                GetRtspConnectionMaster     ()	                            { return m_rtspConnectionMaster; };
    std::string		            GetRTSPUrl                  ()	                            { return m_rtspUrl; };
    int			                GetStalingThreshold         ()	                            { return m_stalingThreshold; };
    CAM_TYPE    	            GetType                     ()	                            { return m_type; };
    std::string		            GetUser                     ()	                            { return m_user; };
    std::string			        GetLocalIP					() 	                            { return m_localIP; };
	int					        GetLocalPort				() 	                            { return m_localPort; };
	std::string 		        GetMulticastIP				() 	                            { return m_multicastIP; };
	int 				        GetMulticastPort			() 	                            { return m_multicastPort; };
    std::string                 GetOptionRequest            ()                              { return m_optionRequest; };
	std::string			        GetRemoteIP					() 	                            { return m_remoteIP; };
	int					        GetRemotePort				() 	                            { return m_remotePort; };
    int 				        GetReceivePoolBufferSize	() 	                            { return m_receivePoolBufferSize; };
	int 				        GetReceivePoolSize			() 	                            { return m_receivePoolSize; };
    VIDEO_DECODER_TYPE 			GetVideoDecoderType			() 	                            { return m_videoDecoderType; };
    VIDEO_DECODER_OUTPUT_TYPE   GetVideoDecoderOutputType	() 	                            { return m_videoDecoderOutputType; };
    
    void		                SetDecodedImageBufferSize   (int val)				        { m_decodedImageBufferSize = val; };
    void		                SetDecodedImagePoolSize     (int val)				        { m_decodedImagePoolSize = val; };
    void		                SetEnabled                  (bool val)                      { m_enabled = val; };
    void		                SetFramerate                (int val)				        { m_framerate = val; };
    void		                SetId                       (int val)                       { m_id = val; };
    void                        SetImageHeight              (int val)                       { m_imageHeight = val; };
    void                        SetImageNumChannels         (int val)                       { m_imageNumChannels = val; };
    void                        SetImageWidth               (int val)                       { m_imageWidth = val; };
    void                        SetMaxTimeInRTPQueue        (int val)                       { m_maxTimeInRTPQueue = val; };
    void		                SetPassword                 (std::string val)               { m_password = val; };
    void		                SetRtspConnectionMaster     (bool val)                      { m_rtspConnectionMaster = val; };
    void		                SetRTSPUrl                  (std::string val)               { m_rtspUrl = val; };
    void		                SetStalingThreshold         (int threshold);
    void		                SetType                     (CAM_TYPE val)                  { m_type = val; };
    void		                SetUser                     (std::string val)               { m_user = val; };
    void				        SetLocalIP					(std::string val) 		        { m_localIP = val; };
	void				        SetLocalPort				(int val) 				        { m_localPort = val; };
	void 				        SetMulticastIP				(std::string val) 		        { m_multicastIP = val; };
	void 				        SetMulticastPort			(int val) 				        { m_multicastPort = val; };
    void                        SetOptionRequest            (std::string val)               { m_optionRequest = val;};
	void				        SetRemoteIP					(std::string val) 		        { m_remoteIP = val; };
	void				        SetRemotePort				(int val) 				        { m_remotePort = val; };
    void 				        SetReceivePoolBufferSize	(int val) 				        { m_receivePoolBufferSize = val; };
	void 				        SetReceivePoolSize			(int val) 				        { m_receivePoolSize = val; };
    void 				        SetVideoDecoderType			(VIDEO_DECODER_TYPE val) 		{ m_videoDecoderType = val; };
    void 				        SetVideoDecoderOutputType	(VIDEO_DECODER_OUTPUT_TYPE val) { m_videoDecoderOutputType = val; };

    void Clear	()
    {
        m_decodedImageBufferSize    = -1;
        m_decodedImagePoolSize      = -1;
        m_enabled                   = false;
        m_framerate                 = -1;
        m_id                        = -1;
        m_imageHeight               = -1;
        m_imageNumChannels          = -1;
        m_imageWidth                = -1;
        m_maxTimeInRTPQueue         = -1;
        m_password                  = "";
        m_rtspConnectionMaster      = false;
        m_rtspUrl                   = "";
        m_stalingThreshold          = -1;
        m_type                      = CT_UNKNOWN;
        m_user                      = "";
        m_localIP                   = "";
	    m_localPort                 = -1;
        m_multicastIP               = "";
	    m_multicastPort             = -1;
        m_optionRequest             = "";
	    m_remoteIP                  = "";
	    m_remotePort                = -1;
        m_receivePoolBufferSize     = -1;
	    m_receivePoolSize           = -1;
        m_videoDecoderType          = VDT_NONE;
        m_videoDecoderOutputType    = VDOT_NONE;
   };

    CCameraConfig& operator =(const CCameraConfig& rhs)
    {
        if(this != &rhs)
        {
            this->m_decodedImageBufferSize      = rhs.m_decodedImageBufferSize;
            this->m_decodedImagePoolSize        = rhs.m_decodedImagePoolSize;
            this->m_enabled                     = rhs.m_enabled;
            this->m_framerate                   = rhs.m_framerate;
            this->m_id                          = rhs.m_id;
            this->m_imageHeight                 = rhs.m_imageHeight;
            this->m_imageNumChannels            = rhs.m_imageNumChannels;
            this->m_imageWidth                  = rhs.m_imageWidth;
            this->m_maxTimeInRTPQueue           = rhs.m_maxTimeInRTPQueue;
            this->m_password                    = rhs.m_password;
            this->m_rtspConnectionMaster        = rhs.m_rtspConnectionMaster;
            this->m_rtspUrl                     = rhs.m_rtspUrl;
            this->m_stalingThreshold            = rhs.m_stalingThreshold;
            this->m_type                        = rhs.m_type;
            this->m_user                        = rhs.m_user;
            this->m_localIP                     = rhs.m_localIP;
	        this->m_localPort                   = rhs.m_localPort;
            this->m_multicastIP                 = rhs.m_multicastIP;
	        this->m_multicastPort               = rhs.m_multicastPort;
            this->m_optionRequest               = rhs.m_optionRequest;
	        this->m_remoteIP                    = rhs.m_remoteIP;
	        this->m_remotePort                  = rhs.m_remotePort;
            this->m_receivePoolBufferSize       = rhs.m_receivePoolBufferSize;
	        this->m_receivePoolSize             = rhs.m_receivePoolSize;
            this->m_videoDecoderType            = rhs.m_videoDecoderType;
            this->m_videoDecoderOutputType      = rhs.m_videoDecoderOutputType;
        }

        return *this;
    };

private:
    //Camera Parameters
    int                         m_decodedImageBufferSize;
    int                         m_decodedImagePoolSize;
    bool		                m_enabled;
    int			                m_framerate;
    int                         m_id;
    int                         m_imageHeight;
    int                         m_imageNumChannels;
    int                         m_imageWidth;
    int                         m_maxTimeInRTPQueue;
    std::string		            m_password;
    std::string                 m_optionRequest;
    bool		                m_rtspConnectionMaster;
    std::string                 m_rtspUrl;
    int			                m_stalingThreshold;
    CAM_TYPE    	            m_type;
    std::string		            m_user;
    VIDEO_DECODER_TYPE          m_videoDecoderType;
    VIDEO_DECODER_OUTPUT_TYPE   m_videoDecoderOutputType;


    //IO Connection Parameters
    std::string			        m_localIP;
	int					        m_localPort;
    std::string 		        m_multicastIP;
	int 				        m_multicastPort;
	std::string			        m_remoteIP;
	int					        m_remotePort;
    int 				        m_receivePoolBufferSize;
	int 				        m_receivePoolSize;
};