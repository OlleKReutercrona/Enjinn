#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include <D3dx12.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

struct IDXGISwapChain3;
struct ID3D12Device;
struct ID3D12Resource;
struct ID3D12CommandAllocator;
struct ID3D12CommandQueue;
struct ID3D12RootSignature;
struct ID3D12DescriptorHeap;
struct ID3D12PipelineState;
struct ID3D12GraphicsCommandList;
struct ID3D12Fence;

namespace Enj {
	struct D12RendererCreationParams {
		OMath::Vector2ui windowSize;
	};

	class D12Renderer {
	public:
		D12Renderer(const D12RendererCreationParams& params);
		D12Renderer(const D12Renderer& renderer) = delete;
		void operator=(const D12Renderer& renderer) = delete;

		void Init(const HWND& hwnd);
		void Render();
		void Destroy();

		void OnResize(const OMath::Vector2ui windowSize);
	private:
		void LoadPipeline(const HWND& hwnd);
		void LoadAssets();
		void PopulateCommandList();
		void WaitForPreviousFrame();

	private:
		static const UINT sFrameCount = 2;

		struct Vertex {
			OMath::Vector3f mPosition;
			OMath::Vector4f mColor;
		};

		OMath::Vector2ui mWindowSize;

		// Adapter info.
		bool mUseWarpDevice;

		// Pipeline objects
		CD3DX12_VIEWPORT mViewport;
		CD3DX12_RECT mScissorRect;
		ComPtr<IDXGISwapChain3> mSwapChain;
		ComPtr<ID3D12Device> mDevice;
		ComPtr<ID3D12Resource> mRenderTargets[sFrameCount];
		ComPtr<ID3D12CommandAllocator> mCommandAllocator;
		ComPtr<ID3D12CommandQueue> mCommandQueue;
		ComPtr<ID3D12RootSignature> mRootSignature;
		ComPtr<ID3D12DescriptorHeap> mRTVHeap;
		ComPtr<ID3D12PipelineState> mPipelineState;
		ComPtr<ID3D12GraphicsCommandList> mCommandList;
		UINT mRTVDescSize;

		// App Resources
		ComPtr<ID3D12Resource> mVertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;

		// Sync objects
		UINT mFrameIndex;
		HANDLE mFenceEvent;
		ComPtr<ID3D12Fence> mFence;
		UINT64 mFenceValue;
	};
}

