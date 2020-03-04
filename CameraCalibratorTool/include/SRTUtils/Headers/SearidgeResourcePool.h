#pragma once

#include "ThreadSafe.h"
#include "SearidgeSmartPtr.h"

template <class T> class CSearidgeResourcePool
{
public:
	CSearidgeResourcePool(void)
	{
		m_size.Set(-1);
		m_currentReadingPosition.Set(-1);
		m_resourcePtrs = NULL;
	};

	~CSearidgeResourcePool(void)
	{
		Clean();
	};

	CSearidgeSmartPtr<T>*				GetNextAvailabeleResourcePtr	(bool& error);
	unsigned int						GetPoolSize						();
	CSearidgeSmartPtr<T>*				GetResourcePtrs					();

	void								Init							(unsigned int poolSize);

	void								Reset							();

private:
	void								Clean							();

	CThreadSafe<unsigned int>			m_size;
	CSearidgeSmartPtr<T>*				m_resourcePtrs;
	CThreadSafe<unsigned int>			m_currentReadingPosition;
};

template<class T> void CSearidgeResourcePool<T>::Clean()
{
	if (m_resourcePtrs != NULL)
	{
		delete[] m_resourcePtrs;
		m_resourcePtrs = NULL;
	}
	m_size.Set(-1);
	m_currentReadingPosition.Set(-1);
}

template<class T> CSearidgeSmartPtr<T>* CSearidgeResourcePool<T>::GetNextAvailabeleResourcePtr(bool& error)
{
	CSearidgeSmartPtr<T>* retVal = NULL;
	error = false;
	unsigned int lastReadIndex = m_currentReadingPosition.Get();
	unsigned int poolSize = m_size.Get();
	if (lastReadIndex < 0 || poolSize < 0)
	{
		//The pool is not initialized
		error = true;
		return NULL;
	}

	//Look for empty buffer starting at the buffer past the latest read buffer. Also handle wrap around of reading index.
	unsigned int curReadIndex = lastReadIndex + 1;
	if (curReadIndex > poolSize)
	{
		curReadIndex = 0;
	}

	for (; curReadIndex < poolSize; curReadIndex++)
	{
		retVal = &m_resourcePtrs[curReadIndex];

		if (retVal->GetRefCount() == 0)
		{
			m_currentReadingPosition.Set(curReadIndex);
			return retVal;
		}
	}

	if (curReadIndex != lastReadIndex)
	{
		unsigned int upperBound = lastReadIndex;
		for (curReadIndex = 0; curReadIndex < upperBound; curReadIndex++)
		{
			retVal = &m_resourcePtrs[curReadIndex];

			if (retVal->GetRefCount() == 0)
			{
				m_currentReadingPosition.Set(curReadIndex);
				return retVal;
			}
		}
	}

	//No available object found
	error = true;
	return NULL;
}

template<class T> unsigned int CSearidgeResourcePool<T>::GetPoolSize()
{
	return m_size;
}

template<class T> CSearidgeSmartPtr<T>* CSearidgeResourcePool<T>::GetResourcePtrs()
{
	return m_resourcePtrs;
}

template<class T> void CSearidgeResourcePool<T>::Init(unsigned int poolSize)
{
	m_currentReadingPosition.Set(0);
	m_size.Set(poolSize);

	 try
	 {
	 	m_resourcePtrs = new CSearidgeSmartPtr<T>[poolSize];
	 }
	 catch(std::exception& e)
	 {
		if(m_resourcePtrs)
		{
			delete[] m_resourcePtrs;
		}
		printf("Caught an exception in CSearidgeResourcePool::Init. Info: %s", e.what());
	 }
}

template<class T> void CSearidgeResourcePool<T>::Reset()
{
	for (unsigned int i = 0; i < m_size.Get(); i++)
	{
		m_resourcePtrs[i].ResetRefCount();
	}
	m_currentReadingPosition.Set(0);
}
