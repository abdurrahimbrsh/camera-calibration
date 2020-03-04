#pragma once
#include "ThreadSafe.h"

template <class T> class CSearidgeRAObjectPool
{
public:
	CSearidgeRAObjectPool(void)
	{
		m_currentReadingPosition.Set(-1);
		m_objects = NULL;
		m_size.Set(-1);
	};

	~CSearidgeRAObjectPool(void)
	{
		Clean();
	};

	T*					GetNextAvailabeleObject		(bool& error);

	void				Init						(int poolSize, void* objectConstructorArg);

	void				Reset						();

private:
	void				Clean					();

	CThreadSafe<int>			m_currentReadingPosition;
	T**							m_objects;
	CThreadSafe<int>			m_size;
};

template<class T> void CSearidgeRAObjectPool<T>::Clean()
{
	if (m_objects != NULL)
	{
		for (int i = 0; i < m_size.Get(); i++)
		{
			if (m_objects[i])
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
		delete[] m_objects;
		m_objects = NULL;
	}

	m_size.Set(-1);
	m_currentReadingPosition.Set(-1);
}
template<class T> T* CSearidgeRAObjectPool<T>::GetNextAvailabeleObject(bool& error)
{
	T* retVal = NULL;
	error = false;
	int lastReadIndex = m_currentReadingPosition.Get();
	int poolSize = m_size.Get();
	if (lastReadIndex < 0 || poolSize < 0)
	{
		//The pool is not initialized
		error = true;
		return NULL;
	}

	//Look for empty buffer starting at the buffer past the latest read buffer. Also handle wrap around of reading index.
	int curReadIndex = lastReadIndex + 1;
	if (curReadIndex > poolSize)
	{
		curReadIndex = 0;
	}

	for (; curReadIndex < poolSize; curReadIndex++)
	{
		retVal = m_objects[curReadIndex];

		if (!retVal->GetIsInUse())
		{
			m_currentReadingPosition.Set(curReadIndex);
			retVal->SetIsInUse(true);
			return retVal;
		}
	}

	if (curReadIndex != lastReadIndex)
	{
		int upperBound = lastReadIndex;
		for (curReadIndex = 0; curReadIndex < upperBound; curReadIndex++)
		{
			retVal = m_objects[curReadIndex];

			if (!retVal->GetIsInUse())
			{
				m_currentReadingPosition.Set(curReadIndex);
				retVal->SetIsInUse(true);
				return retVal;
			}
		}
	}

	//New available object found
	error = true;
	return NULL;
}

template<class T> void CSearidgeRAObjectPool<T>::Init(int poolSize, void* objectConstructorArg)
{
	m_currentReadingPosition.Set(0);

	if (m_size.Get() == -1)
	{
		m_size.Set(poolSize);

		try
		{
			m_objects = new T*[poolSize];

			for (int i = 0; i < poolSize; i++)
			{
				m_objects[i] = new T(objectConstructorArg);
			}
		}
		catch(std::exception& e)
		{
			if(m_objects)
			{
				for (int i = 0; i < poolSize; i++)
				{
					if(m_objects[i])
					{
						delete m_objects[i];
					}
				}
				delete[] m_objects;
			}
			printf("Caught an exception in CSearidgeRAObjectPool::Init. Info: %s", e.what());
		}
	}
	else
	{
		Reset();
	}
}

template<class T> void CSearidgeRAObjectPool<T>::Reset()
{
	for (int i = 0; i < m_size.Get(); i++)
	{
		if (m_objects[i])
		{
			m_objects[i]->SetIsInUse(false);
		}
	}
	m_currentReadingPosition.Set(0);
}
