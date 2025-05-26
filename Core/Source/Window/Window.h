#pragma once
#include <Math/Vector2.h>

namespace Enj {
	class Engine;

	struct WindowCreationParams {
		OMath::Vector2ui windowSize;
		std::wstring windowName;
		HINSTANCE hInstance;
		int cmdShow;
		Engine* engine;
		WNDPROC windowProc;
	};

	class Window {
	public:
		Window(const WindowCreationParams& creationParams);
		Window(const Window& window) = delete;
		void operator=(const Window& window) = delete;

		void SetWindowSize(const OMath::Vector2ui& windowSize);
		const OMath::Vector2ui& WindowSize() const;

		void SetWindowTitle(const std::wstring& windowTitle);
		void SetWindowCustomText(const std::wstring& text);
		const std::wstring WindowName() const;

		HWND Hwnd();

	private:
		void ApplyWindowText();

		std::wstring mTitle;
		std::wstring mCustomText;
		OMath::Vector2ui mWindowSize;
		float mAspectRatio;
		HWND mHWND;
	};
}

