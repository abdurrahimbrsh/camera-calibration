/* 
 * File:   CSimplerPerformanceRecord_Base.h
 * Author: bakhadur
 *
 * Created on April 17, 2017, 3:21 PM
 */

#ifndef CSIMPLERPERFORMANCERECORD_BASE_H
#define	CSIMPLERPERFORMANCERECORD_BASE_H

#include <pthread.h>

typedef struct _SimplePerformanceValueTime
{
    double val;
    long long tick;
} SimplePerformanceValueTime;

class CSimplerPerformanceRecord_Base
{
public:
    CSimplerPerformanceRecord_Base();
    CSimplerPerformanceRecord_Base(const CSimplerPerformanceRecord_Base& orig);
    virtual ~CSimplerPerformanceRecord_Base();
    
    virtual void UpdateValue(double val)
    {
        pthread_mutex_lock(&m_section);
        m_value.val = val;
        pthread_mutex_unlock(&m_section);
    };
    virtual double GetLatestValue()
    {
        pthread_mutex_lock(&m_section);
        double v = m_value.val;
        pthread_mutex_unlock(&m_section);
        return v;
    };
    
protected:
    SimplePerformanceValueTime m_value;
    pthread_mutex_t m_section;
};

#endif	/* CSIMPLERPERFORMANCERECORD_BASE_H */

