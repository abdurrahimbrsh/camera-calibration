#pragma once

class CJitterTracker
{
public:
	CJitterTracker();
	~CJitterTracker();

	void							AddTimestamp(unsigned int tStamp);

	double							GetAverageJitter();

private:
	double							GateValue(double value);

	double							m_alpha;
	double							m_currentAverage;
	double							m_fiveFPS;
	unsigned int                    m_prevTimestamp;
	double							m_thirtyFPS;
};

