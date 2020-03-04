#pragma once

#include "GenericBuffer.h"
#include "cuda.h"

class CGenericGPUBuffer : public CGenericBuffer
{
public:
	CGenericGPUBuffer(void)
	{
		SetType(GBT_GPU);
		m_pBuf = 0;
		m_error = "";
		Init(GENERIC_BUFFER_DEFAULT_SIZE);
	};
	CGenericGPUBuffer(void* objectConstructorArg)
	{
		SetType(GBT_GPU);
		m_pBuf = 0;
		m_error = "";
		unsigned int* bufSize = (unsigned int*)objectConstructorArg;
		Init(*bufSize);
	};
	~CGenericGPUBuffer()
	{
		cuMemFree(m_pBuf);
	};

	CUdeviceptr GetGPUBuf(){ return m_pBuf; };

	unsigned int	GetH264SourceSize() { return m_h264SourceSize; };

	void			SetH264SourceSize(unsigned int size) { m_h264SourceSize = size; };

protected:
	void Init(unsigned int bufSize)
	{
		if (bufSize > 1)
		{
			CUresult error = cuMemAlloc(&m_pBuf, bufSize);
			if (error != CUresult::CUDA_SUCCESS)
			{
				char errorMsg[1024];
				sprintf(errorMsg, "CUDA Error Num = %d", error);
				m_error = errorMsg;
			}
		}
		SetSize(bufSize);
	};

private:
	CUdeviceptr		m_pBuf;				//Buffer
	unsigned int	m_h264SourceSize;	//Size of the h264 data which was source for the bitmap stored in this buffer
};