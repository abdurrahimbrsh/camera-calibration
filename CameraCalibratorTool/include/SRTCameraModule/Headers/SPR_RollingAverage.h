/* 
 * File:   SPR_RollingAverage.h
 * Author: bakhadur
 *
 * Created on April 17, 2017, 3:25 PM
 */

#ifndef SPR_ROLLINGAVERAGE_H
#define	SPR_ROLLINGAVERAGE_H

#include <list>
#include "SimplerPerformanceRecord_Base.h"

class CSPR_RollingAverage : public CSimplerPerformanceRecord_Base 
{
public:
    CSPR_RollingAverage();
    CSPR_RollingAverage(const CSPR_RollingAverage& orig);
    virtual ~CSPR_RollingAverage();
    
    double GetAverage();
    virtual double GetLatestValue();
    void Reset();
    void SetSampleLengthSec(unsigned int seconds){ m_sampleLengthSec = seconds; };
    virtual void UpdateValue(double val);
    int GetCount();
    
    
protected:
    unsigned int m_sampleLengthSec;
    std::list<SimplePerformanceValueTime> m_values;
};

#endif	/* SPR_ROLLINGAVERAGE_H */

