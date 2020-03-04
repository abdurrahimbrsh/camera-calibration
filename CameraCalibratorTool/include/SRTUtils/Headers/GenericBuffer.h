#pragma once

#include <string>

#define GENERIC_BUFFER_DEFAULT_SIZE	6220800 // 3 Channel HD bitmap

typedef enum GENERIC_BUF_TYPE
{
	GBT_NONE = 0,
	GBT_CPU = 1,
	GBT_GPU = 2
} GENERIC_BUF_TYPE;

typedef enum GENERIC_BUF_DAT_TYPE
{
	GBT_DT_INVALID = 0,
	GBT_DT_RGB = 1,
	GBT_DT_YUV420 = 2,
	GBT_DT_NV12 = 3
} GENERIC_BUF_DAT_TYPE;

class CGenericBuffer
{
public:
	CGenericBuffer(void)
	{
		m_sz = 0;
		m_len = 0;
		m_fillTick = 0;
		m_inUse = false;
		m_interFrameDelay = 0.0;
		m_dataType = GBT_DT_INVALID;
		m_lineSize = 0;
		m_error = "";
		m_type = GBT_NONE;
	};

	CGenericBuffer(void* objectConstructorArg)
	{
		m_sz = 0;
		m_len = 0;
		m_fillTick = 0;
		m_inUse = false;
		m_interFrameDelay = 0.0;
		m_dataType = GBT_DT_INVALID;
		m_lineSize = 0;
		m_lineHeight = 0;
		m_lineWidth = 0;
		m_error = "";
		m_type = GBT_NONE;
	};
	virtual ~CGenericBuffer()
	{
		m_sz = 0;
		m_len = 0;
		m_fillTick = 0;
		m_inUse = false;
		m_interFrameDelay = 0.0;
		m_dataType = GBT_DT_INVALID;
	};

	GENERIC_BUF_DAT_TYPE	GetDataType()								{ return m_dataType; };
	bool					GetErrors(std::string& error)				{ if (!m_error.empty()){ error.empty(); error = m_error; return true; } return false; }
	int						GetLineSize()								{ return m_lineSize; }
	int						GetLineHeight()								{ return m_lineHeight; }
	int						GetLineWidth()								{ return m_lineWidth; }
	void					SetDataType(GENERIC_BUF_DAT_TYPE dataType) { m_dataType = dataType; };
	void					SetLineSize(int lineSize)					{ m_lineSize = lineSize; }
	void					SetLineHeight(int lineHeight)				{ m_lineHeight = lineHeight; }
	void					SetLineWidth(int lineWidth)					{ m_lineWidth = lineWidth; }

	unsigned long			GetFillTick			()								{ return m_fillTick; };
	bool					GetIsInUse			()								{ return m_inUse; };
	unsigned int			GetLength			()								{ return m_len; };
	unsigned int			GetSize				()								{ return m_sz; };
	GENERIC_BUF_TYPE		GetType				()								{ return m_type; };
	double					GetInterFrameDelay	()								{ return m_interFrameDelay; };

	void					SetFillTick			(unsigned long fillTick)		{ m_fillTick = fillTick; };
	void					SetIsInUse			(bool inUse)					{ m_inUse = inUse; };
	void					SetLength			(unsigned int length)			{ m_len = length; };
	void					SetInterFrameDelay	(double delay)					{ m_interFrameDelay = delay; };


protected:
	virtual void			Init				(unsigned int bufSize) = 0;

	void					SetSize				(unsigned int size)				{ m_sz = size; };
	void					SetType				(GENERIC_BUF_TYPE type)			{ m_type = type; };
	std::string					m_error;

private:
	unsigned int			m_sz; //Static size of the buffer
	unsigned int			m_len; //dynamic length of the data currently in the buffer
	unsigned long			m_fillTick; //Tick of the buffer fill time
	bool					m_inUse;			//Usage flag
	GENERIC_BUF_TYPE		m_type;				//Type
	double					m_interFrameDelay;	//Delay for jitter correction

	GENERIC_BUF_DAT_TYPE	m_dataType;			//Data type
	int						m_lineSize;
	int						m_lineHeight;
	int						m_lineWidth;
};