// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd; //()메인 윈도우 핸들

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         //실행된 프로세스의 시작 주소
                     _In_opt_ HINSTANCE hPrevInstance,  
                     _In_ LPWSTR    lpCmdLine,          //해당 프로그램에 실행할 때 넣어줄 추가 명령어 받아오기
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // hInstance에 IDS_APP_TITLE(109)에 해당하는 문자정보를 프로젝트 리소스 테이블인 string table에서 가지고와 szTitle에 집어넣어라
                                                                    //이게 있는 이유 : 프로그램 처음실행하면 맨위 창의 이름을 정의하기 위해, 없으면 기본 프로젝트이름
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING); //szWindowClass는 MyRegisterClass의 키값 파트이다.

    //윈도우 정보 등록
    MyRegisterClass(hInstance);

    //윈도우 생성
    if (!InitInstance (hInstance, nCmdShow)) // MyRegisterClass에서 키값을 찾아 InitInstanc로 만든다.
    {
        return FALSE;
    }

    //단축키 관련 정보
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    //()강제로 타임 셋을 시키는 방법
    //SetTimer(g_hWnd, 10, 0, nullptr);

    // 기본 메시지 루프입니다:
    /*
    while (GetMessage(&msg, nullptr, 0, 0)) //GetMessage는 해당프로그램쪽으로 발생한 메시지들을 메시지 큐에 받아놔서 그걸 꺼내보는것
        //GetMessage 특징
        //메시지 큐에서 메시지 확인 할 때 까지 대기
        //GetMessage의 false 반환 : msg.message == WM_QUIT -> while문 종료
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    //KillTimer(g_hWnd, 10);
    //()변경한 메시지 루프
    //비교시간체크
    DWORD dwPrevCount = GetTickCount();
    int iMsgCheck = 0;
    int iNoneMsgCheck = 0;
    while (true) 
    {
        //PeekMessage
        //메세지 유무와 관계없이 반환
        //메시지큐에서 메시지를 확인한 경우 true, 메시지큐에 메시지가 없는 경우 false로 반환
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))//슬적본다(&msg, nullptr, 0, 0,자기가 확인한 메시지가 있는 경우 메시지 큐에서 제거(없으면 메시지 큐에 계속 존재)
                                                     //메시지의 유무로 ture false 반환
        {
            //메시지 처리하기전
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            ++iMsgCheck;
        }
        else
        {
            //메시지가 없는 동안 호출
            ++iNoneMsgCheck;
            DWORD dwCurCount = GetTickCount();
            if (dwCurCount - iNoneMsgCheck > 1000)
            {
                int a = 0;
            }
        }
    }
    

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance) // 윈도우 실행시 모든 정보 셋팅
{
    WNDCLASSEXW wcex; //윈도우 클래스 확장

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle/*창이름*/, WS_OVERLAPPEDWINDOW, //HWND는 CreateWindowW에서 ID를 받고 다룰수 있게 된다.
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);                                                      //아이디 값을 받아서 ShowWindow하게 된다.
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

//마우스좌표확인을 위한 전역변수
/*
int g_x = 0;
int g_y = 0;
*/

#include <vector>

using std::vector;

//클라이언트 오브젝트 그리기 (윈도우 에서 재공하는 기본 int 구조체)
struct tOpjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

//오브젝트들을 저장할 수 있는 동적 메모리
vector<tOpjInfo> g_vecInfo;

//좌상단에 기억
POINT g_ptLT;
//우하단에 기억
POINT g_ptRB;
//마우스 왼쪽버튼 bool
bool bLbtnDown = false;


LRESULT CALLBACK WndProc(HWND g_hWnd, UINT message, WPARAM wParam, LPARAM lParam)//wParam,lParam은 해당 message의 부가 인자값
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), g_hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(g_hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: //window에 무효화 영역이 발생한 경우 발생 : 판정) 창을 줄였다 켜진경우
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(g_hWnd, &ps); //Device Context : 그리기 , hWnd : window이다.
            //BeginPaint : Device Context하나를 만들어서 ID를 반환해주는 함수
             /*
            struct __HDC
            {
                int a;
            }typedef HDC; ->이런식으로 만들어진다. */

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            // 
            //즉. HDC는 Device Context의 ID를 받는 자료형이다.
            
            //DC의 목적지는 hWnd
            //DC의 펜은 기본팬(Black)
            //DC의 브러쉬는 기본 브러쉬(white)
            // 
            //직접 펜, 브러쉬를 만들어 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
            HBRUSH hBluebrush = CreateSolidBrush(RGB(0, 0, 255));//GetStockObject는 자주사용하는 도구들의 모음집
            //기존 펜, 브러쉬 값을 받아옴
            HPEN hDefaultPen =  (HPEN)SelectObject(hdc, hRedPen);//hdc에 hRedPen를 선택해라 
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBluebrush);
           
            //윈도우 헨들, 윈도우 좌표, HDC 
            //윈도우 좌표 : 작업영역(타이틀바와 매뉴바 밑에서 시작함), 0,0은 좌상단을 말함, 1단위는 픽셀
            //윈도우 핸들 : H붙어있으면 모두 핸들, DI값을 받는 자료형
            //HDC : 
            
            //사각형그리기
            /*
            Rectangle(hdc
                , g_ptObjPos.x - g_ptObjScale.x / 2
                , g_ptObjPos.y - g_ptObjScale.y / 2
                , g_ptObjPos.x + g_ptObjScale.x / 2
                , g_ptObjPos.y + g_ptObjScale.y / 2);*/
            //왼쪽 마우스 버튼을 눌렀을때 사각형 그리기
            if (bLbtnDown)
            {
                Rectangle(hdc, g_ptLT.x, g_ptLT.y, g_ptRB.x, g_ptRB.y);
            }
            //vector안에 추가된 사각형 그리기
            for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                Rectangle(hdc
                    , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
                    , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
                    , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
                    , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }


            //다시 원래 팬, 브러쉬 받기
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);
            //만든펜,브러쉬 지우기
            DeleteObject(hRedPen);
            DeleteObject(hBluebrush);

            //그리기 종료
            EndPaint(g_hWnd, &ps);
        }
        break;

    //키보드의 키가 눌리면 발생하는 함수
    case WM_KEYDOWN: //WM_KEYDOWN한번 눌린후 그다음 계속들어옴
    {
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjPos.y -= 10;
            InvalidateRect(g_hWnd, nullptr, true); //무효화영역을 직접 설정
            break;
        case VK_DOWN:
            //g_ptObjPos.y += 10;
            InvalidateRect(g_hWnd, nullptr, true); //무효화영역을 직접 설정
            break;
        case VK_LEFT:
            //g_ptObjPos.x -= 10;
            InvalidateRect(g_hWnd, nullptr, true); //무효화영역을 직접 설정
            break;
        case VK_RIGHT:
            //g_ptObjPos.x += 10;
            InvalidateRect(g_hWnd, nullptr, true); //무효화영역을 직접 설정
            break;
        }
    }
        break;

    //마우스 왼쪽 클릭 눌렀을 때
    case WM_LBUTTONDOWN:  //lParam = 마우스 좌표
    {
        g_ptLT.x = LOWORD(lParam); //마우스 x좌표
        g_ptLT.y = HIWORD(lParam); //마우스 y좌표
        bLbtnDown = true;
    }
        break;

    case WM_MOUSEMOVE: //마우스가 이동할때 발생하는 이벤트
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(g_hWnd, nullptr, true);
    }
        break;

    case WM_LBUTTONUP:
    {
        tOpjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x); //abs = 절댓값
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;
        InvalidateRect(g_hWnd, nullptr, true);
    }
        break;

    case WM_TIMER:
    {
        int a = 0;
    }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(g_hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
