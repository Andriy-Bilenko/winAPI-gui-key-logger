#include "Window.hpp"
#pragma comment(lib, "gdi32.lib")//for coloring

//initializing static variables
HHOOK Window::g_hKeyboardHook = NULL;
Window* Window::g_pWindow = NULL;

Window::Window(HINSTANCE hInstance)
    : m_hInstance(hInstance)
    , m_hWnd(nullptr)
{
    g_pWindow = this;
}

Window::~Window()
{
    if (m_hWnd)
    {
        DestroyWindow(m_hWnd);
        DestroyWindow(m_hLabel);
        m_hWnd = nullptr;
        m_hLabel = nullptr;
    }
}
MSG Window::DestroyWin(){
    UnhookWindowsHookEx(g_hKeyboardHook);
    DestroyWindow(m_hWnd);
    DestroyWindow(m_hLabel);
    return m_msg;
}

bool Window::Create(LPCTSTR lpWindowName, int width, int height)
{
    WNDCLASSEX wc = { 0 };
    //Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = Window::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(40, 0, 0));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("LoggerWindowClass");
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if (!RegisterClassEx(&wc)){
        MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    m_hWnd = CreateWindowEx(
        WS_EX_TOPMOST,// Window style
        TEXT("LoggerWindowClass"),// Window class name
        lpWindowName,// Window title
        WS_OVERLAPPEDWINDOW,// Window style
        CW_USEDEFAULT, CW_USEDEFAULT,// Window position
        width, height, // Window size
        NULL, NULL, m_hInstance, NULL);     
    if (m_hWnd == NULL) {
        MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    // Remove the resizable flag
    LONG_PTR style = GetWindowLongPtr(m_hWnd, GWL_STYLE);
    style &= ~WS_THICKFRAME;
    SetWindowLongPtr(m_hWnd, GWL_STYLE, style);
    //create label:
    m_hLabel = CreateWindowEx(
    0,// Control style
    TEXT("STATIC"),// Control class name
    TEXT(""),// Control text
    WS_CHILD | WS_VISIBLE,// Control style
    10, 10,// Control position
    (width - 40), (height - 60),// Control size
    m_hWnd,// Parent window handle
    NULL, m_hInstance, NULL);
    if (m_hLabel == NULL) {
        MessageBox(NULL, TEXT("Static Control Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    return true;
}

bool Window::SetHook(){
    g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, GetModuleHandle(NULL), 0);
    if (g_hKeyboardHook == NULL) {
        MessageBox(NULL, TEXT("Keyboard Hook Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    return true;
}

void Window::Show(int nCmdShow)
{
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);
}

void Window::Update()
{
    while (GetMessage(&m_msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }
}


LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);    
        break;
    }
    return 0;
}

//simple function for replacing part of a string, used later on
bool replace_std_string(std::string& s, std::string const& toReplace, std::string const& replaceWith) 
{
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return false;
    s.replace(pos, toReplace.length(), replaceWith); return true;
}

LRESULT CALLBACK Window::KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;//contains information about the keyboard input event
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            //this variable will contain a string showing what key (key-sequence) is being pressed at the moment
            std::string text = "";
            char buffer[256] = { 0 };
            int key = pKeyboard->vkCode;

            // Determine the key name
            int keyNameLength = GetKeyNameTextA(pKeyboard->scanCode << 16, buffer, sizeof(buffer));
            if (keyNameLength > 0) {
                text += buffer ;
            } else {
                // If key name is not available, use virtual key code
                text += std::to_string(key);
            }

            // Add key modifiers to the text
            if (pKeyboard->flags & LLKHF_EXTENDED) {//check for extended keys
                text.insert(0, "Extended+");
            }
            if (GetKeyState(VK_SHIFT) & 0x8000) {//the most significant bit shows if pressed
                text.insert(0, "Shift+");
            }
            if (GetKeyState(VK_CONTROL) & 0x8000) {
                text.insert(0, "Ctrl+");
            }
            if (GetKeyState(VK_MENU) & 0x8000) {
                text.insert(0, "Alt+");
            }
            //keys, that were not shown properly:
            replace_std_string(text, "Extended+Num 0", "Ins/Numlock");
            replace_std_string(text, "Extended+Num 1", "End");
            replace_std_string(text, "Extended+Num 2", "Down");
            replace_std_string(text, "Extended+Num 3", "Pgdn");
            replace_std_string(text, "Extended+Num 4", "Left");
            replace_std_string(text, "Extended+Num 6", "Right");
            replace_std_string(text, "Extended+Num 7", "Home");
            replace_std_string(text, "Extended+Num 8", "Up");
            replace_std_string(text, "Extended+Num 9", "Pgup");
            replace_std_string(text, "Extended+Num Del", "Del");
            replace_std_string(text, "Extended+91", "Meta");
            if(g_pWindow->m_labelText.length() > 260) g_pWindow->m_labelText.clear();//for refreshing the text every time we run out of space
            if(g_pWindow->m_labelText.length() % 26 == 0) g_pWindow->m_labelText += "\n";//for going on another line evry time we aproach right border
            g_pWindow->m_labelText += text + " ";//separating keys
            //need this construction for disabling warnings with type conversion
            std::wstring wstrText(g_pWindow->m_labelText.begin(), g_pWindow->m_labelText.end());
            const wchar_t* wideText = wstrText.c_str();
            SetWindowTextW(g_pWindow->m_hLabel, wideText);
        }
    }
    return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);//passing to the next in a hook chain
}
