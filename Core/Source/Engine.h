#pragma once
#include <Math/Vector2.h>

struct IDXGIAdapter1;
struct IDXGIFactory1;

namespace Enj {
	class Window;
	class D12Renderer;

	struct FrameData {
		const float mDeltaTime;
		const float mTotalTime;
	};


	class Engine {
	public:
		Engine();
		Engine(const Engine& engine) = delete;
		void operator=(const Engine& engine) = delete;
		~Engine();

		void Init(std::shared_ptr<Enj::Window> window);
		void Update(const FrameData& frameData);
		void Render(const FrameData& frameData);
		void Destroy();

		const OMath::Vector2ui& GetWindowSize();
		const std::wstring& GetTitle() const;

		void ParseCommandLineArgs(_In_reads_(argc) wchar_t* argv[], int argc);

		// event handling
		void OnResize(const OMath::Vector2ui windowSize);

	private:
		std::wstring GetAssetFullPath(wchar_t* assetName);

		IDXGIAdapter1* GetHardwareAdapter(
			_In_ IDXGIFactory1* factory,
			bool requestHighPerformanceAdapter = false);

		void SetCustomWindowText(const std::wstring& text);

		std::shared_ptr<Window> mWindow;
		std::unique_ptr<D12Renderer> mRenderer;

		bool mUseWarpDevice;

		std::wstring mAssetsPath;
		std::wstring mTitle;
	};
}

