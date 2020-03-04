#pragma once

#include <string>

using namespace std;

class CSearidgeSimpleMessage
{
public:
    
    CSearidgeSimpleMessage(void);
    ~CSearidgeSimpleMessage(void);

    void                Init                    (unsigned long nodeId, string CDA_ID, unsigned char* nodeInfoBufferPtr, unsigned long bufferLen);

    bool                IsComplete              ()		{return m_isComplete;};
    unsigned char*	GetBodyPtr              ()		{return m_bodyBufferPtr;};
    int			GetBodyLen              ();

    unsigned char*	GetHeaderPtr            ()		{return m_msgHeader;}
    virtual int         GetHeaderLen            ()		{return 0;};

    unsigned char*	GetFooterPtr            ()		{return m_msgFooter;}
    virtual	int     GetFooterLen            ()		{return 0;};

    virtual int		AddDataUntilYouAreFull  (unsigned char* dataIn, int len) {return 0;};

    virtual void        Clear                   ();

    int			GetNodeID               ();
    unsigned long long	GetTimestamp            ()		{return m_timestamp;};

    virtual string      GetLastErrorMsg         ();

protected:
    
    void		InitBuffer();

    unsigned char*          m_dataBlock;
    unsigned int            m_dataBlockEndPos;

    bool                    m_isComplete;

    unsigned char*          m_startToken;
    unsigned int            m_startTokenLen;
    unsigned char*          m_startToken_NONADEXP;
    unsigned char*          m_endToken;
    unsigned int            m_endTokenLen;

    unsigned char*          m_msgHeader;
    unsigned char*          m_msgFooter;

    unsigned char*          m_bodyBufferPtr;

    int                     m_lastErrNum;
    string                  m_errDetails;
    unsigned long long      m_timestamp;

    typedef enum MSG_ERR
    {
            BODY_INCOMG_DATA_TOO_LONG,
            BODY_BUFFER_SIZE_EXCEDED,
            BODY_START_TOKEN_UNFOUND,
            BODY_INVALID_HEADER,
            BODY_MSG_TOO_LONG,
            BODY_END_TOKEN_UNFOUND
    } CASDMSG_ERR;
	
    static const int MAX_MSG_BUFSIZE = 2000000;
};