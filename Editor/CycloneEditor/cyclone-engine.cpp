#include "Window.h"

#include <Windows.h>

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    CycloneEditor::Window* appWindow = new CycloneEditor::Window("Cyclone Engine");
    if (!appWindow->init())
        return -1;

    appWindow->run();
    appWindow->cleanup();

    delete appWindow;

    return 0;
}