#pragma once

#include <pthread.h>

template <class genT>
class CThreadSafe
{
public:
	CThreadSafe(void)		{pthread_mutex_init(&m_section, NULL);};
	CThreadSafe(genT val)	{Set(val);};
	~CThreadSafe(void) 		{};

	void Set(const genT& val)
	{
		pthread_mutex_lock(&m_section);
		m_val = val;
		pthread_mutex_unlock(&m_section);
	};

	genT Get()
	{
		pthread_mutex_lock(&m_section);
		genT retVal = m_val;
		pthread_mutex_unlock(&m_section);
		return retVal;
	};

private:
	pthread_mutex_t m_section;
	genT m_val;
};
