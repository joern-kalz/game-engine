#pragma once

#include "gmock/gmock.h"

#include "../../windows-runtime/Graphics/GraphicsLibrary.h"

class GraphicsLibraryMock : public GraphicsLibrary {
public:
	MOCK_METHOD(HRESULT, CreateDevice, (
		IDXGIAdapter* p_adapter,
		D3D_DRIVER_TYPE driver_type,
		HMODULE software,
		UINT flags,
		D3D_FEATURE_LEVEL* p_feature_levels,
		UINT feature_levels,
		UINT SDKVersion,
		winrt::com_ptr<ID3D11Device>* device,
		D3D_FEATURE_LEVEL* p_feature_level,
		winrt::com_ptr<ID3D11DeviceContext>* context
		), (override));

	MOCK_METHOD(void, asDevice3, (
		winrt::com_ptr<ID3D11Device>* device,
		winrt::com_ptr<ID3D11Device3>* device_3
		), (override));

	MOCK_METHOD(void, asContext3, (
		winrt::com_ptr<ID3D11DeviceContext>* context,
		winrt::com_ptr<ID3D11DeviceContext3>* context_3
		), (override));

	MOCK_METHOD(HRESULT, CreateBuffer, (
		winrt::com_ptr<ID3D11Device3>* device,
		const D3D11_BUFFER_DESC* p_desc,
		const D3D11_SUBRESOURCE_DATA* p_initial_data,
		ID3D11Buffer** pp_buffer
		), (override));

	MOCK_METHOD(HRESULT, CreateSamplerState, (
		winrt::com_ptr<ID3D11Device3>* device,
		const D3D11_SAMPLER_DESC* p_sampler_desc,
		ID3D11SamplerState** pp_sampler_state
		), (override));

	MOCK_METHOD(void, Trim, (
		winrt::com_ptr<ID3D11Device3>* device
		), (override));
};
