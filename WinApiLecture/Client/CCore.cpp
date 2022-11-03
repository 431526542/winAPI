#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"


CObject g_obj;

//동적할당을 통한 싱글톤 방식
//CCore* CCore::g_pInst = nullptr;
//싱글톤으로 만든 유일한 객체를 데이터 영역에 올리는 방식
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
	ReleaseDC(m_hWnd, m_hDC);//m_hWnd에 있는 m_hDC제거

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0,0,m_ptResolution.x,m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100,100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	//이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	//Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	

	//Object설정
	g_obj.SetPos(Vec2( (float) m_ptResolution.x / 2, (float) m_ptResolution.y / 2 ));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}
/*
int CCore::init()
{
	/*
	HRESULT hr = S_OK;//윈도우에서 제공해주는 대부분 함수 결과값이 HRESULT(long)타입이다.
	if (FAILED(hr))//FAILED : 윈도우에서 자주 사용하는 메크로 : 음수면 true
	{

	}
	E_FAIL; //실패했을때 반환하는 값이 음수
	return E_FAIL;
	//return S_OK; //성공했을때 반환하는 값이 0
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

	//이동관련
	update();
	//그리기
	render();
	
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	//물체들의 변경점 체크
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//지금 이순간에 눌렸는지 확인하는 법
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
	//화면 클리어
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	//그리기
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
