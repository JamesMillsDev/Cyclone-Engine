#include "window.h"
#include "debug.h"

using CycloneEngine::window;

int main()
{
    window* appWindow = new window("Cyclone Engine");
    if (!appWindow->init())
        return -1;

    appWindow->run();
    appWindow->cleanup();

    delete appWindow;

    return 0;
}