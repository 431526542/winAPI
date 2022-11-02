#include "pch.h"
#include "CCore.h"
#include "CObject.h"


CObject g_obj;

//�����Ҵ��� ���� �̱��� ���
//CCore* CCore::g_pInst = nullptr;



//�̱������� ���� ������ ��ü�� ������ ������ �ø��� ���
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);//m_hWnd�� �ִ� m_hDC����
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100,100 };

	return S_OK;
}
/*
int CCore::init()
{
	/*
	HRESULT hr = S_OK;//�����쿡�� �������ִ� ��κ� �Լ� ������� HRESULT(long)Ÿ���̴�.
	if (FAILED(hr))//FAILED : �����쿡�� ���� ����ϴ� ��ũ�� : ������ true
	{

	}
	E_FAIL; //���������� ��ȯ�ϴ� ���� ����
	return E_FAIL;
	//return S_OK; //���������� ��ȯ�ϴ� ���� 0
}*/


void CCore::progress()
{
	static int callcount = 0;
	++callcount;

	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}
	update();
	render();
	
}

void CCore::update()
{
	//��ü���� ������ üũ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//���� �̼����� ���ȴ��� Ȯ���ϴ� ��
	{
		g_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
	
}

void CCore::render()
{
	//�׸���
	Rectangle(m_hDC
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}