#include "pch.h"
#include "CCore.h"
#include "CObject.h"


CObject g_obj;

//동적할당을 통한 싱글톤 방식
//CCore* CCore::g_pInst = nullptr;



//싱글톤으로 만든 유일한 객체를 데이터 영역에 올리는 방식
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);//m_hWnd에 있는 m_hDC제거
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

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100,100 };

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
	//물체들의 변경점 체크
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//지금 이순간에 눌렸는지 확인하는 법
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
	//그리기
	Rectangle(m_hDC
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
