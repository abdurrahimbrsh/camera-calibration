#pragma once

#include "GenericBuffer.h"

class CGenericCPUBuffer : public CGenericBuffer
{
public:
	CGenericCPUBuffer(void)
	{
		SetType(GBT_CPU);
		m_pBuf = NULL;

		Init(GENERIC_BUFFER_DEFAULT_SIZE);
	};
	CGenericCPUBuffer(void* objectConstructorArg)
	{
		SetType(GBT_CPU);
		m_pBuf = NULL;

		unsigned int* bufSize = (unsigned int*)objectConstructorArg;
		Init(*bufSize);
	};
	~CGenericCPUBuffer()
	{
		if (m_pBuf != NULL)
		{
			delete[] m_pBuf;
			m_pBuf = NULL;
		}
	};

	unsigned char* GetCPUBuf(){ return m_pBuf; };

protected:
	void Init(unsigned int bufSize)
	{
		m_pBuf = new unsigned char[bufSize];
		SetSize(bufSize);
	};

private:
	unsigned char*		m_pBuf; //buffer
};