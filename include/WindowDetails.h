#ifndef WINDOW_DETAILS_H
#define WINDOW_DETAILS_H

#include "raylib.h"

class WindowDetails{
public:
    WindowDetails(int winWidth, int winHeight);
    int GetDisplayWidth();
    int GetDisplayHeight();
    void ToggleFullScreenWindow(int windowWidth, int windowHeight);
    int getWindowWidth() { return windowWidth; }
    int getWindowHeight() { return windowHeight; }
private:
    int windowWidth{};
    int windowHeight{};
};

#endif