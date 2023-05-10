#pragma once
#include <Windows.h>
#include <string>

class Window
{
public:
    //prepares Window* for KeyboardHook() function (because it is static)
    Window(HINSTANCE hInstance);
    //deletes window and label handle
    ~Window();
    //creates window handle, label, shows errors in messageboxes if couldn't register window, create window, create label
    bool Create(LPCTSTR lpWindowName, int width, int height);
    //shows and redraws window
    void Show(int nCmdShow);
    //infinite loop that processes messages sent to the application's message queue
    void Update();
    //sets keyboard hook, shows error in a messagebox if fails
    bool SetHook();
    //clears up and returns last message (whether the program ended gracefully)
    MSG DestroyWin();
private:
    //processes messages sent to the window
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    //intercepts keyboard input and prints to the Window label keys pressed
    static LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);

    //member variables:
    HINSTANCE m_hInstance{};
    HWND m_hWnd{};
    MSG m_msg = {};
    HWND m_hLabel{};
    std::string m_labelText{};
    //global ones:
    static HHOOK g_hKeyboardHook;//also for KeyboardHook()
    static Window* g_pWindow;//for accessing non-static members from KeyboardHook()
};
