#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"


CObject g_obj;

//�����Ҵ��� ���� �̱��� ���
//CCore* CCore::g_pInst = nullptr;
//�̱������� ���� ������ ��ü�� ������ ������ �ø��� ���
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);//m_hWnd�� �ִ� m_hDC����

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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

	//���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	//Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	

	//Object����
	g_obj.SetPos(Vec2( (float) m_ptResolution.x / 2, (float) m_ptResolution.y / 2 ));
	g_obj.SetScale(Vec2(100, 100));

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
	/*
	static int callcount = 0;
	++callcount;

	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}*/
	//Manager Update
	CTimeMgr::GetInst()->update();

	//�̵�����
	update();
	//�׸���
	render();
	
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	//��ü���� ������ üũ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//���� �̼����� ���ȴ��� Ȯ���ϴ� ��
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetDT();
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	//ȭ�� Ŭ����
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	//�׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_memDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}
