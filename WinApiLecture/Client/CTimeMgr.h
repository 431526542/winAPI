#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; //프레임 간의 시간값
	double m_dAcc; //1초 체크를 위한 누적 시간
	UINT m_iCallCount; //함수 호출 회수 체크
	UINT m_iFPS; //초당 호출 횟수

	// FPS 알아야한다.
	// 1 프레임당 시간을 알 수 있다. (Delta Time)

public:
	void init(); //초기화 목적
	void update(); //매 프레임마다 호출

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

