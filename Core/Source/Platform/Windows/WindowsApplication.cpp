#include "WindowsApplication.h"
#include "Engine.h"
#include "Window/Window.h"


int WindowsApplication::Run(HINSTANCE hInstance, int cmdShow) {
    Enj::Engine engine;

    Enj::WindowCreationParams windowCreationParams;
    windowCreationParams.cmdShow = cmdShow;
    windowCreationParams.hInstance = hInstance;
    windowCreationParams.engine = &engine;
    windowCreationParams.windowName = L"Enjinn Engine";
    windowCreationParams.windowSize = {1280,720};
    windowCreationParams.windowProc = WindowProc;
    
    auto window = std::make_shared<Enj::Window>(windowCreationParams);
    
    engine.Init(std::move(window));

    MSG msg = {};
    while (msg.message != WM_QUIT) {

        // Process queued messages
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        engine.Update();
        engine.Render();
    }

    engine.Destroy();

    return static_cast<char>(msg.wParam);
}

LRESULT WindowsApplication::WindowProc(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam) {

    Enj::Engine* engine = reinterpret_cast<Enj::Engine*>(GetWindowLongPtr(hWND, GWLP_USERDATA));

    switch (message) {
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    case WM_SIZE: {
        engine->OnResize({LOWORD(lParam), HIWORD(lParam)});
    }
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWND, message, wParam, lParam);
}
