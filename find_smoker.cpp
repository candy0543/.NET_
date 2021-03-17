#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void RegMyWndClass(LPCWSTR cname);
void MakeWindow(LPCWSTR cname);
void MsgLoop();
INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
    RegMyWndClass(TEXT("HelloEH"));
    MakeWindow(TEXT("HelloEH"));
    MsgLoop();
}
void RegMyWndClass(LPCWSTR cname)
{
    //윈도우 클래스 속성 설정
    WNDCLASS wndclass = { 0 };
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hInstance = GetModuleHandle(0);
    wndclass.hIcon = LoadIcon(0, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    wndclass.lpfnWndProc = MyWndProc;
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = cname;
    wndclass.style = MY_DEF_STYLE;
    //윈도우 클래스 등록
    RegisterClass(&wndclass);
}
void MakeWindow(LPCWSTR cname)
{
    //윈도우 개체 생성
    HWND hWnd = CreateWindow(cname,//클래스 이름
        TEXT("타이틀"),//타이틀 명
        WS_OVERLAPPEDWINDOW,//윈도우 스타일
        100, 30, 700, 600,//Left, Top, Width, Height
        0, //부모 윈도우 핸들
        0,//메뉴
        GetModuleHandle(0),//모듈 핸들
        0 //WM_CREATE에 전달할 인자       
    );
    //윈도우 개체 시각화
    ShowWindow(hWnd, SW_SHOW);
}
void MsgLoop()
{
    MSG Message;
    while (GetMessage(&Message, 0, 0, 0))//응용 큐에서 메시지를 꺼내오기
    {
        DispatchMessage(&Message);//메시지 수행(콜백 가동)
    }
}
#define IDC_GENDER 0x01
#define IDB_CONFIRM 0x02
#define IDB_MALE        0x03
#define IDB_FEMALE   0x04
#define IDS_GENDER 0x05
#define IDR_ONE     0x6
#define IDR_TWO     0x7
#define IDR_THREE 0x8

void OnCreate(HWND hWnd)
{
    HINSTANCE hIns = GetModuleHandle(0);
    
}
void OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);//WM_QUIT 메시지를 발급
    //이를 통해 MSG LOOP을 탈출할 수 있게 함
}
void OnDraw(HDC hdc)
{
    //그리기 작업
}
void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    OnDraw(ps.hdc);
    EndPaint(hWnd, &ps);
}


void OnCommand(HWND hWnd, WORD cid, WORD cmsg, HWND cWnd)
{
    switch (cid)
    {    
    }
}
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_CREATE: OnCreate(hWnd); return 0;
    case WM_COMMAND: OnCommand(hWnd, LOWORD(wParam), HIWORD(wParam), (HWND)lParam); return 0;
    case WM_PAINT: OnPaint(hWnd); return 0;
    case WM_DESTROY: OnDestroy(hWnd); return 0;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
