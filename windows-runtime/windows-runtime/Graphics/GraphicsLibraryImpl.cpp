#include "pch.h"
#include "GraphicsLibraryImpl.h"


HRESULT GraphicsLibraryImpl::CreateDevice(
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
) {
	return D3D11CreateDevice(
		p_adapter,
		driver_type,
		software,
		flags,
		p_feature_levels,
		feature_levels,
		SDKVersion,
		device ? device->put() : nullptr,
		p_feature_level,
		context ? context->put() : nullptr
	);
}

void GraphicsLibraryImpl::asDevice3(
	winrt::com_ptr<ID3D11Device>* device,
	winrt::com_ptr<ID3D11Device3>* device_3
) {
	(*device_3) = device->as<ID3D11Device3>();
}

void GraphicsLibraryImpl::asContext3(
	winrt::com_ptr<ID3D11DeviceContext>* context,
	winrt::com_ptr<ID3D11DeviceContext3>* context_3
) {
	(*context_3) = context->as<ID3D11DeviceContext3>();
}

HRESULT GraphicsLibraryImpl::CreateBuffer(
	winrt::com_ptr<ID3D11Device3>* device,
	const D3D11_BUFFER_DESC* p_desc,
	const D3D11_SUBRESOURCE_DATA* p_initial_data,
	ID3D11Buffer** pp_buffer
) {
	return (*device)->CreateBuffer(
		p_desc, 
		p_initial_data, 
		pp_buffer
	);
}

HRESULT GraphicsLibraryImpl::CreateSamplerState(
	winrt::com_ptr<ID3D11Device3>* device,
	const D3D11_SAMPLER_DESC* p_sampler_desc,
	ID3D11SamplerState** pp_sampler_state
) {
	return (*device)->CreateSamplerState(
		p_sampler_desc,
		pp_sampler_state
	);
}

void GraphicsLibraryImpl::Trim(
	winrt::com_ptr<ID3D11Device3>* device
) {
	device->as<IDXGIDevice3>()->Trim();
}

