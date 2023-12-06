#include "WindowDetails.h"


WindowDetails::WindowDetails(int winWidth, int winHeight):
    windowWidth(winWidth), windowHeight(winHeight)
{
    InitWindow(getWindowWidth(), getWindowHeight(), "Legends of Myhria");
    SetWindowPosition(100, 100); // where window appears on screen
};

int WindowDetails::GetDisplayWidth()
{
    if (IsWindowFullscreen())
    {
        return GetMonitorWidth(GetCurrentMonitor());
    }
    else
    {
        return GetScreenWidth();
    }
}

int WindowDetails::GetDisplayHeight()
{
    if (IsWindowFullscreen())
    {
        return GetMonitorHeight(GetCurrentMonitor());
    }
    else
    {
        return GetScreenHeight();
    }
}

void WindowDetails::ToggleFullScreenWindow(int windowWidth, int windowHeight)
{
    if (!IsWindowFullscreen())
    {
        // int monitor = GetCurrentMonitor();
        // SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        // GetDisplayWidth();
        // GetDisplayHeight();
        ToggleFullscreen();
    }
    else
    {
        ToggleFullscreen();
        // SetWindowSize(windowWidth, windowHeight);
    }
}
