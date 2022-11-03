#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; //������ ���� �ð���
	double m_dAcc; //1�� üũ�� ���� ���� �ð�
	UINT m_iCallCount; //�Լ� ȣ�� ȸ�� üũ
	UINT m_iFPS; //�ʴ� ȣ�� Ƚ��

	// FPS �˾ƾ��Ѵ�.
	// 1 �����Ӵ� �ð��� �� �� �ִ�. (Delta Time)

public:
	void init(); //�ʱ�ȭ ����
	void update(); //�� �����Ӹ��� ȣ��

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

