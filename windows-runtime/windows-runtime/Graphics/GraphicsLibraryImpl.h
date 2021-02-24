#pragma once

#include "GraphicsLibrary.h"

class GraphicsLibraryImpl : public GraphicsLibrary {
public:
	virtual HRESULT CreateDevice(
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
	);

	virtual void asDevice3(
		winrt::com_ptr<ID3D11Device>* device,
		winrt::com_ptr<ID3D11Device3>* device_3
	);

	virtual void asContext3(
		winrt::com_ptr<ID3D11DeviceContext>* context,
		winrt::com_ptr<ID3D11DeviceContext3>* context_3
	);

	virtual HRESULT CreateBuffer(
		winrt::com_ptr<ID3D11Device3>* device,
		const D3D11_BUFFER_DESC* p_desc,
		const D3D11_SUBRESOURCE_DATA* p_initial_data,
		ID3D11Buffer** pp_buffer
	);

	virtual HRESULT CreateSamplerState(
		winrt::com_ptr<ID3D11Device3>* device,
		const D3D11_SAMPLER_DESC* p_sampler_desc,
		ID3D11SamplerState** pp_sampler_state
	);

	virtual void Trim(
		winrt::com_ptr<ID3D11Device3>* device
	);
};