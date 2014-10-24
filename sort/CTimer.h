#ifndef CTIMER_HH
#define CTIMER_HH
class CTimer
{
public:
	CTimer()
	{
		QueryPerformanceFrequency(&m_Frequency);
		Start();
	}
	void Start()
	{
		QueryPerformanceCounter(&m_StartCount);
	}
	double End()
	{
		LARGE_INTEGER CurrentCount;
		QueryPerformanceCounter(&CurrentCount);
		return double(CurrentCount.LowPart - m_StartCount.LowPart) *1000/ (double)m_Frequency.LowPart;
	}
	void ShowNow()
	{
		LARGE_INTEGER CurrentCount;
		QueryPerformanceCounter(&CurrentCount);
		cout<<"Timer Count is:"<<double(CurrentCount.LowPart - m_StartCount.LowPart)*1000 / (double)m_Frequency.LowPart<<endl;
	}
private:
	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_StartCount;
};
#endif
