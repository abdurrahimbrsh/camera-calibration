#pragma once

#include <pthread.h>

template <class T> class CSearidgeSmartPtr
{
public:

	CSearidgeSmartPtr()
	{
		m_pPayload = NULL;
		m_refCount = 0;
		pthread_mutex_init(&m_refCountSection, NULL);
		m_timestamp = 0;
	};

	~CSearidgeSmartPtr()
	{
		DeletePayload();
	};

	void 			DecrementRefCount	();
	void 			DeletePayload		();

	T*	 			GetPayload			();
	unsigned int 	GetRefCount			();

	void 			IncrementRefCount	();

	void 			ResetRefCount		();

	void 			SetPayload			(T* payload);
	void 			SetRefCount			(unsigned int refNum);

private:

	T*							m_pPayload; 		//Buffer
	unsigned int				m_refCount; 		//Counter to keep track of how many times this pointer is currently referenced
	pthread_mutex_t				m_refCountSection;	//Critical section for the reference count
	unsigned long				m_timestamp; 		//Tick of the buffer fill time
};

template<class T> void CSearidgeSmartPtr<T>::DecrementRefCount()
{
	pthread_mutex_lock(&m_refCountSection);

	if (m_refCount > 0)
	{
		m_refCount = m_refCount - 1;
	}

	pthread_mutex_unlock(&m_refCountSection);
}

template<class T> void CSearidgeSmartPtr<T>::DeletePayload()
{
	if (m_pPayload)
	{
		delete m_pPayload;
		m_pPayload = NULL;
	}
}

template<class T> T* CSearidgeSmartPtr<T>::GetPayload()
{
	return m_pPayload;
}

template<class T> unsigned int CSearidgeSmartPtr<T>::GetRefCount()
{
	unsigned int retVal = 0;

	pthread_mutex_lock(&m_refCountSection);

	retVal = m_refCount;

	pthread_mutex_unlock(&m_refCountSection);

	return retVal;
}

template<class T> void CSearidgeSmartPtr<T>::IncrementRefCount()
{
	pthread_mutex_lock(&m_refCountSection);

	m_refCount = m_refCount + 1;

	pthread_mutex_unlock(&m_refCountSection);
}

template<class T> void CSearidgeSmartPtr<T>::ResetRefCount()
{
	pthread_mutex_lock(&m_refCountSection);

	m_refCount = 0;

	pthread_mutex_unlock(&m_refCountSection);
}

template<class T> void CSearidgeSmartPtr<T>::SetPayload(T* payload)
{
	m_pPayload = payload;
}

template<class T> void CSearidgeSmartPtr<T>::SetRefCount(unsigned int refNum)
{
	pthread_mutex_lock(&m_refCountSection);

	m_refCount = refNum;

	pthread_mutex_unlock(&m_refCountSection);
}
