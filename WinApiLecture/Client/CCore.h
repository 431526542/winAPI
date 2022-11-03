#pragma once


//�̱��� ����
//��ü�� ������ 1���� ����
//��𼭵� ������ ����

//�����Ҵ��� ���� �̱��� ���
/*
class CCore
{
private:
	static CCore* g_pInst;

public:
	//�����ɹ� �Լ�
	static CCore* GetInstance()
	{
		//2�� �̻� ȣ�� �� ���
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		return g_pInst;
	}

	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}
	


private:
	CCore();
	~CCore();
};*/

//�̱������� ���� ������ ��ü�� ������ ������ �ø��� ���
class CCore
{
	SINGLE(CCore);

private:
	HWND m_hWnd; //���� ������ �ڵ�
	POINT m_ptResolution; //���� ������ �ػ�
	HDC m_hDC; //���� �����쿡 Draw�� DC

	//���߹��۸�
	HBITMAP m_hBit;
	HDC m_memDC;

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }

};