#include "Window.h"

Enj::Window::Window(const WindowCreationParams& creationParams) :
    mWindowSize(creationParams.windowSize),
    mTitle(creationParams.windowName) {
    mAspectRatio = static_cast<float>(mWindowSize.mX) / static_cast<float>(mWindowSize.mY);

    // Initialize the window class.
    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = creationParams.windowProc;
    windowClass.hInstance = creationParams.hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = mTitle.c_str();
    RegisterClassEx(&windowClass);

    RECT windowRect = { 0, 0, static_cast<LONG>(mWindowSize.mX), static_cast<LONG>(mWindowSize.mY) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and store a handle to it.
    mHWND = CreateWindow(
        windowClass.lpszClassName,
        mTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        creationParams.hInstance,
        creationParams.engine);

    ShowWindow(mHWND, creationParams.cmdShow);
}

void Enj::Window::SetWindowSize(const OMath::Vector2ui& windowSize) {
    mWindowSize = windowSize;
}

const OMath::Vector2ui& Enj::Window::WindowSize() const {
    return mWindowSize;
}

void Enj::Window::SetWindowTitle(const std::wstring& windowName) {
    mTitle = windowName;

    ApplyWindowText();
}

void Enj::Window::SetWindowCustomText(const std::wstring& text) {
    mCustomText = L": " + text;

    ApplyWindowText();
}

const std::wstring& Enj::Window::WindowName() const {
    return mTitle + L": " + mCustomText;
}

HWND Enj::Window::Hwnd() {
    return mHWND;
}

void Enj::Window::ApplyWindowText() {
    std::wstring windowText = mTitle + mCustomText;
    SetWindowText(mHWND, windowText.c_str());
}
