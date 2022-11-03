#pragma once


//싱글톤 패턴
//객체의 생성을 1개로 제한
//어디서든 접근이 가능

//동적할당을 통한 싱글톤 방식
/*
class CCore
{
private:
	static CCore* g_pInst;

public:
	//정적맴버 함수
	static CCore* GetInstance()
	{
		//2번 이상 호출 될 경우
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

//싱글톤으로 만든 유일한 객체를 데이터 영역에 올리는 방식
class CCore
{
	SINGLE(CCore);

private:
	HWND m_hWnd; //메인 윈도우 핸들
	POINT m_ptResolution; //메인 윈도우 해상도
	HDC m_hDC; //메인 윈도우에 Draw할 DC

	//이중버퍼링
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