#include <Windows.h>

#include "src/Window.h"

int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    const auto appWindow = new CycloneEditor::Window("Cyclone Engine");
    if (!appWindow->Init())
        return -1;

    appWindow->Run();
    appWindow->Cleanup();

    delete appWindow;

    return 0;
}
