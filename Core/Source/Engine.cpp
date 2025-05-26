#include "stdafx.h"

#include "Engine.h"
#include "Window/Window.h"
#include "Graphics/D12Renderer.h"

using namespace Microsoft::WRL;

Enj::Engine::Engine() {
    // Parse the command line parameters
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    ParseCommandLineArgs(argv, argc);
    LocalFree(argv);

	// Maybe shouldn't be here?
	{
		WCHAR assetsPath[512];
		if (assetsPath == nullptr) {
			throw std::exception();
		}

		DWORD size = GetModuleFileName(nullptr, assetsPath, 512);
		if (size == 0 || size == 512) {
			// Method failed or path was truncated.
			throw std::exception();
		}

		WCHAR* lastSlash = wcsrchr(assetsPath, L'\\');
		if (lastSlash) {
			*(lastSlash + 1) = L'\0';
		}
		mAssetsPath = assetsPath;
	}
}

//*********************************************************************************
Enj::Engine::~Engine() {}

//*********************************************************************************
void Enj::Engine::Init(std::shared_ptr<Enj::Window> window) {
    mWindow = std::move(window);

    D12RendererCreationParams params;
    params.windowSize = mWindow->WindowSize();
    mRenderer = std::make_unique<D12Renderer>(params);
    mRenderer->Init(mWindow->Hwnd());
}

//*********************************************************************************
void Enj::Engine::Update(const FrameData& frameData) {
    mRenderer->Update(frameData);
}

//*********************************************************************************
void Enj::Engine::Render(const FrameData& frameData) {
    mRenderer->Render(frameData);
}

//*********************************************************************************
void Enj::Engine::Destroy() {}

//*********************************************************************************
const OMath::Vector2ui& Enj::Engine::GetWindowSize() {
    return mWindow->WindowSize();
}

//*********************************************************************************
const std::wstring& Enj::Engine::GetTitle() const {
	return mWindow->WindowName();
}

//*********************************************************************************
_Use_decl_annotations_
void Enj::Engine::ParseCommandLineArgs(wchar_t* argv[], int argc) {
    for (int i = 1; i < argc; ++i) {
        if (_wcsnicmp(argv[i], L"-warp", wcslen(argv[i])) == 0 ||
            _wcsnicmp(argv[i], L"/warp", wcslen(argv[i])) == 0) {
            mUseWarpDevice = true;
            mTitle = mTitle + L" (WARP)";
        }
    }
}

//*********************************************************************************
//
//                                 EVENT HANDLING
//
//*********************************************************************************
void Enj::Engine::OnResize(const OMath::Vector2ui windowSize) {
    windowSize;
}

//*********************************************************************************
std::wstring Enj::Engine::GetAssetFullPath(wchar_t* assetName) {
	return mAssetsPath + assetName;
}

//*********************************************************************************
_Use_decl_annotations_
IDXGIAdapter1* Enj::Engine::GetHardwareAdapter(IDXGIFactory1* factory, bool requestHighPerformanceAdapter) {
    ComPtr<IDXGIAdapter1> adapter;

    ComPtr<IDXGIFactory6> factory6;
    if (SUCCEEDED(factory->QueryInterface(IID_PPV_ARGS(&factory6)))) {
        for (
            UINT adapterIndex = 0;
            SUCCEEDED(factory6->EnumAdapterByGpuPreference(
                adapterIndex,
                requestHighPerformanceAdapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED,
                IID_PPV_ARGS(&adapter)));
                ++adapterIndex) {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
                // Don't select the Basic Render Driver adapter.
                // If you want a software adapter, pass in "/warp" on the command line.
                continue;
            }

            // Check to see whether the adapter supports Direct3D 12, but don't create the
            // actual device yet.
            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
                break;
            }
        }
    }

    if (adapter.Get() == nullptr) {
        for (UINT adapterIndex = 0; SUCCEEDED(factory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex) {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
                // Don't select the Basic Render Driver adapter.
                // If you want a software adapter, pass in "/warp" on the command line.
                continue;
            }

            // Check to see whether the adapter supports Direct3D 12, but don't create the
            // actual device yet.
            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
                break;
            }
        }
    }

    return adapter.Detach();
}

//*********************************************************************************
void Enj::Engine::SetCustomWindowText(const std::wstring& text) {
    mWindow->SetWindowTitle(text);
}
