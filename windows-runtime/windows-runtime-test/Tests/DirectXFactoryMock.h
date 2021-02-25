#pragma once

#include "gmock/gmock.h"

#include "../../windows-runtime/Graphics/DirectXFactory.h"

class DirectXFactoryMock : public DirectXFactory {
public:
	MOCK_METHOD(HRESULT, CreateDevice, (
		IDXGIAdapter* p_adapter,
		D3D_DRIVER_TYPE driver_type,
		HMODULE software,
		UINT flags,
		D3D_FEATURE_LEVEL* p_feature_levels,
		UINT feature_levels,
		UINT SDKVersion,
		ID3D11Device** device,
		D3D_FEATURE_LEVEL* p_feature_level,
		ID3D11DeviceContext** context
	), (override));
};
