#include <Windows.h>
#define MY_DEF_STYLE CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS
// 윈도우의 이동이나 크기 조절 시 클라이언트의 세로,가로의 크기가 변경되면 다시 그림 
// 더블 클릭하면 더블 클릭 메시지를 윈도우 프로시저로 보냄 

int ticks;
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void RegMyWndClass(LPCWSTR cname);
void MakeWindow(LPCWSTR cname);
void MsgLoop();
// INT APIENTRY WinMain ( 프로그램의 인스턴스 핸들, 딱히몰라도 무방,명령,프로그램 실행될 형태)
// 서로 다른 인스턴스 핸들값을 가지고 다른 메모리를 차지. 이 인스턴스 핸들값으로 운영체제는 두 개의 같은 프로그램 구별 

INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
{
    // hIns g+h
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
    wndclass.lpfnWndProc = MyWndProc; // 메시지 처리 지정 함수 
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = cname; // ?? 나한테 보여지는 게 아닌가보네 
    wndclass.style = MY_DEF_STYLE;
    //윈도우 클래스 등록
    RegisterClass(&wndclass);
}
void MakeWindow(LPCWSTR cname)
{
    //윈도우 개체 생성
    HWND hWnd = CreateWindow(cname,//클래스 이름
        TEXT("deunnie"),//타이틀 명
        WS_OVERLAPPEDWINDOW,//윈도우 스타일
        100, 30, 700, 600,//Left, Top, Width, Height // CW_USEDEFAULT
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
        // TranslateMessage(&Message)  /메세지 내부 관측 
        DispatchMessage(&Message);//메시지 수행(콜백 가동)
    }
}

SYSTEMTIME st;
VOID CALLBACK OnClock(HWND hWnd, UINT id, UINT_PTR ptr, DWORD dw)
{
    GetLocalTime(&st);
    InvalidateRect(hWnd, 0, TRUE);
}
VOID CALLBACK OnTick(HWND hWnd, UINT id, UINT_PTR ptr, DWORD dw)
{
    ticks++;
    InvalidateRect(hWnd, 0, TRUE);
}
void OnCreate(HWND hWnd)
{
    SetTimer(hWnd, 1, 1000, OnClock);
    SetTimer(hWnd, 2, 10, OnTick);
    SendMessage(hWnd, WM_TIMER, 1, 0);
}
void OnDestroy(HWND hWnd)
{
    KillTimer(hWnd, 1);
    KillTimer(hWnd, 2);
    PostQuitMessage(0);//WM_QUIT 메시지를 발급
    //이를 통해 MSG LOOP을 탈출할 수 있게 함
}

void OnDraw(HWND hWnd, HDC hdc)
{
    WCHAR buf[256];
    wsprintf(buf, TEXT("%02d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond);
    TextOut(hdc, 0, 0, buf, lstrlen(buf));

    wsprintf(buf, TEXT("%015d ticks"), ticks);
    TextOut(hdc, 0, 30, buf, lstrlen(buf));
}
void OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    OnDraw(hWnd, ps.hdc);
    EndPaint(hWnd, &ps);
}

LRESULT CALLBACK MyWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_TIMER: OnClock(hWnd, 0, 0, 0); return 0;
    //case WM_MOVE: 
    // 화면의 어디쯤에서 마우스 버튼이 눌러졌는가 
    //case WM_LBUTTONDOWN : 
    // 메시지가 입력되엇다면 어떤 키가 입력되었는지 
    //case WM_CHAR : 

    case WM_CREATE: OnCreate(hWnd); return 0;
    case WM_PAINT: OnPaint(hWnd); return 0;
    case WM_DESTROY: OnDestroy(hWnd); return 0; // 윈도우 파괴 
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
