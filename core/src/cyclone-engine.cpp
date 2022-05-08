#include "window.h"

#include <Windows.h>

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    window* appWindow = new window("Cyclone Engine");
    if (!appWindow->init())
        return -1;

    appWindow->run();
    appWindow->cleanup();

    delete appWindow;

    return 0;
}