#pragma once

class ID3D11Device3Mock : public ID3D11Device3 {
public:
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateTexture2D1, HRESULT(_In_ const D3D11_TEXTURE2D_DESC1* pDesc1, _In_reads_opt_(_Inexpressible_(pDesc1->MipLevels* pDesc1->ArraySize)) const D3D11_SUBRESOURCE_DATA* pInitialData, _COM_Outptr_opt_ ID3D11Texture2D1** ppTexture2D));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateTexture3D1, HRESULT(_In_ const D3D11_TEXTURE3D_DESC1* pDesc1, _In_reads_opt_(_Inexpressible_(pDesc1->MipLevels)) const D3D11_SUBRESOURCE_DATA* pInitialData, _COM_Outptr_opt_ ID3D11Texture3D1** ppTexture3D));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateRasterizerState2, HRESULT(_In_ const D3D11_RASTERIZER_DESC2* pRasterizerDesc, _COM_Outptr_opt_ ID3D11RasterizerState2** ppRasterizerState));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateShaderResourceView1, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_SHADER_RESOURCE_VIEW_DESC1* pDesc1, _COM_Outptr_opt_ ID3D11ShaderResourceView1** ppSRView1));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateUnorderedAccessView1, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_UNORDERED_ACCESS_VIEW_DESC1* pDesc1, _COM_Outptr_opt_ ID3D11UnorderedAccessView1** ppUAView1));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateRenderTargetView1, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_RENDER_TARGET_VIEW_DESC1* pDesc1, _COM_Outptr_opt_ ID3D11RenderTargetView1** ppRTView1));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateQuery1, HRESULT(_In_ const D3D11_QUERY_DESC1* pQueryDesc1, _COM_Outptr_opt_ ID3D11Query1** ppQuery1));
	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, GetImmediateContext3, void(_Outptr_ ID3D11DeviceContext3** ppImmediateContext));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDeferredContext3, HRESULT(UINT ContextFlags, _COM_Outptr_opt_ ID3D11DeviceContext3** ppDeferredContext));
	MOCK_METHOD6_WITH_CALLTYPE(STDMETHODCALLTYPE, WriteToSubresource, void(_In_ ID3D11Resource* pDstResource, _In_ UINT DstSubresource, _In_opt_ const D3D11_BOX* pDstBox, _In_ const void* pSrcData, _In_ UINT SrcRowPitch, _In_ UINT SrcDepthPitch));
	MOCK_METHOD6_WITH_CALLTYPE(STDMETHODCALLTYPE, ReadFromSubresource, void(_Out_ void* pDstData, _In_ UINT DstRowPitch, _In_ UINT DstDepthPitch, _In_ ID3D11Resource* pSrcResource, _In_ UINT SrcSubresource, _In_opt_ const D3D11_BOX* pSrcBox));

	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, GetImmediateContext2, void(_Outptr_ ID3D11DeviceContext2** ppImmediateContext));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDeferredContext2, HRESULT(UINT ContextFlags, _COM_Outptr_opt_ ID3D11DeviceContext2** ppDeferredContext));
	MOCK_METHOD7_WITH_CALLTYPE(STDMETHODCALLTYPE, GetResourceTiling, void(_In_ ID3D11Resource* pTiledResource, _Out_opt_ UINT* pNumTilesForEntireResource, _Out_opt_ D3D11_PACKED_MIP_DESC* pPackedMipDesc, _Out_opt_ D3D11_TILE_SHAPE* pStandardTileShapeForNonPackedMips, _Inout_opt_ UINT* pNumSubresourceTilings, _In_ UINT FirstSubresourceTilingToGet, _Out_writes_(*pNumSubresourceTilings) D3D11_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CheckMultisampleQualityLevels1, HRESULT(_In_ DXGI_FORMAT Format, _In_ UINT SampleCount, _In_ UINT Flags, _Out_ UINT* pNumQualityLevels));

	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, GetImmediateContext1, void(_Outptr_ ID3D11DeviceContext1** ppImmediateContext));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDeferredContext1, HRESULT(UINT ContextFlags, _COM_Outptr_opt_ ID3D11DeviceContext1** ppDeferredContext));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateBlendState1, HRESULT(_In_ const D3D11_BLEND_DESC1* pBlendStateDesc, _COM_Outptr_opt_ ID3D11BlendState1** ppBlendState));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateRasterizerState1, HRESULT(_In_ const D3D11_RASTERIZER_DESC1* pRasterizerDesc, _COM_Outptr_opt_ ID3D11RasterizerState1** ppRasterizerState));
	MOCK_METHOD7_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDeviceContextState, HRESULT(UINT Flags, _In_reads_(FeatureLevels) const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, _Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel, _Out_opt_ ID3DDeviceContextState** ppContextState));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, OpenSharedResource1, HRESULT(_In_ HANDLE hResource, _In_ REFIID returnedInterface, _COM_Outptr_ void** ppResource));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, OpenSharedResourceByName, HRESULT(_In_ LPCWSTR lpName, _In_ DWORD dwDesiredAccess, _In_ REFIID returnedInterface, _COM_Outptr_ void** ppResource));

	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateBuffer, HRESULT(_In_ const D3D11_BUFFER_DESC* pDesc, _In_opt_ const D3D11_SUBRESOURCE_DATA* pInitialData, _COM_Outptr_opt_ ID3D11Buffer** ppBuffer));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateTexture1D, HRESULT(_In_ const D3D11_TEXTURE1D_DESC* pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels* pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA* pInitialData, _COM_Outptr_opt_ ID3D11Texture1D** ppTexture1D));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateTexture2D, HRESULT(_In_ const D3D11_TEXTURE2D_DESC* pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels* pDesc->ArraySize)) const D3D11_SUBRESOURCE_DATA* pInitialData, _COM_Outptr_opt_ ID3D11Texture2D** ppTexture2D));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateTexture3D, HRESULT(_In_ const D3D11_TEXTURE3D_DESC* pDesc, _In_reads_opt_(_Inexpressible_(pDesc->MipLevels)) const D3D11_SUBRESOURCE_DATA* pInitialData, _COM_Outptr_opt_ ID3D11Texture3D** ppTexture3D));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateShaderResourceView, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, _COM_Outptr_opt_ ID3D11ShaderResourceView** ppSRView));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateUnorderedAccessView, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, _COM_Outptr_opt_ ID3D11UnorderedAccessView** ppUAView));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateRenderTargetView, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, _COM_Outptr_opt_ ID3D11RenderTargetView** ppRTView));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDepthStencilView, HRESULT(_In_ ID3D11Resource* pResource, _In_opt_ const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, _COM_Outptr_opt_ ID3D11DepthStencilView** ppDepthStencilView));
	MOCK_METHOD5_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateInputLayout, HRESULT(_In_reads_(NumElements) const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, _In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT) UINT NumElements, _In_reads_(BytecodeLength) const void* pShaderBytecodeWithInputSignature, _In_ SIZE_T BytecodeLength, _COM_Outptr_opt_ ID3D11InputLayout** ppInputLayout));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateVertexShader, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11VertexShader** ppVertexShader));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateGeometryShader, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11GeometryShader** ppGeometryShader));
	MOCK_METHOD9_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateGeometryShaderWithStreamOutput, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_reads_opt_(NumEntries) const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, _In_range_(0, D3D11_SO_STREAM_COUNT* D3D11_SO_OUTPUT_COMPONENT_COUNT) UINT NumEntries, _In_reads_opt_(NumStrides) const UINT* pBufferStrides, _In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT) UINT NumStrides, _In_ UINT RasterizedStream, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11GeometryShader** ppGeometryShader));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CreatePixelShader, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11PixelShader** ppPixelShader));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateHullShader, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11HullShader** ppHullShader));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDomainShader, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11DomainShader** ppDomainShader));
	MOCK_METHOD4_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateComputeShader, HRESULT(_In_reads_(BytecodeLength) const void* pShaderBytecode, _In_ SIZE_T BytecodeLength, _In_opt_ ID3D11ClassLinkage* pClassLinkage, _COM_Outptr_opt_ ID3D11ComputeShader** ppComputeShader));
	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateClassLinkage, HRESULT(_COM_Outptr_ ID3D11ClassLinkage** ppLinkage));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateBlendState, HRESULT(_In_ const D3D11_BLEND_DESC* pBlendStateDesc, _COM_Outptr_opt_ ID3D11BlendState** ppBlendState));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDepthStencilState, HRESULT(_In_ const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, _COM_Outptr_opt_ ID3D11DepthStencilState** ppDepthStencilState));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateRasterizerState, HRESULT(_In_ const D3D11_RASTERIZER_DESC* pRasterizerDesc, _COM_Outptr_opt_ ID3D11RasterizerState** ppRasterizerState));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateSamplerState, HRESULT(_In_ const D3D11_SAMPLER_DESC* pSamplerDesc, _COM_Outptr_opt_ ID3D11SamplerState** ppSamplerState));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateQuery, HRESULT(_In_ const D3D11_QUERY_DESC* pQueryDesc, _COM_Outptr_opt_ ID3D11Query** ppQuery));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreatePredicate, HRESULT(_In_ const D3D11_QUERY_DESC* pPredicateDesc, _COM_Outptr_opt_ ID3D11Predicate** ppPredicate));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateCounter, HRESULT(_In_ const D3D11_COUNTER_DESC* pCounterDesc, _COM_Outptr_opt_ ID3D11Counter** ppCounter));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CreateDeferredContext, HRESULT(UINT ContextFlags, _COM_Outptr_opt_ ID3D11DeviceContext** ppDeferredContext));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, OpenSharedResource, HRESULT(_In_ HANDLE hResource, _In_ REFIID ReturnedInterface, _COM_Outptr_opt_ void** ppResource));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, CheckFormatSupport, HRESULT(_In_ DXGI_FORMAT Format, _Out_ UINT* pFormatSupport));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CheckMultisampleQualityLevels, HRESULT(_In_ DXGI_FORMAT Format, _In_ UINT SampleCount, _Out_ UINT* pNumQualityLevels));
	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, CheckCounterInfo, void(_Out_ D3D11_COUNTER_INFO* pCounterInfo));
	MOCK_METHOD9_WITH_CALLTYPE(STDMETHODCALLTYPE, CheckCounter, HRESULT(_In_ const D3D11_COUNTER_DESC* pDesc, _Out_ D3D11_COUNTER_TYPE* pType, _Out_ UINT* pActiveCounters, _Out_writes_opt_(*pNameLength) LPSTR szName, _Inout_opt_ UINT* pNameLength, _Out_writes_opt_(*pUnitsLength) LPSTR szUnits, _Inout_opt_ UINT* pUnitsLength, _Out_writes_opt_(*pDescriptionLength) LPSTR szDescription, _Inout_opt_ UINT* pDescriptionLength));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, CheckFeatureSupport, HRESULT(D3D11_FEATURE Feature, _Out_writes_bytes_(FeatureSupportDataSize) void* pFeatureSupportData, UINT FeatureSupportDataSize));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, GetPrivateData, HRESULT(_In_ REFGUID guid, _Inout_ UINT* pDataSize, _Out_writes_bytes_opt_(*pDataSize) void* pData));
	MOCK_METHOD3_WITH_CALLTYPE(STDMETHODCALLTYPE, SetPrivateData, HRESULT(_In_ REFGUID guid, _In_ UINT DataSize, _In_reads_bytes_opt_(DataSize) const void* pData));
	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, SetPrivateDataInterface, HRESULT(_In_ REFGUID guid, _In_opt_ const IUnknown* pData));
	MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, GetFeatureLevel, D3D_FEATURE_LEVEL());
	MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, GetCreationFlags, UINT());
	MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, GetDeviceRemovedReason, HRESULT());
	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, GetImmediateContext, void(_Outptr_ ID3D11DeviceContext** ppImmediateContext));
	MOCK_METHOD1_WITH_CALLTYPE(STDMETHODCALLTYPE, SetExceptionMode, HRESULT(UINT RaiseFlags));
	MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, GetExceptionMode, UINT());

	MOCK_METHOD2_WITH_CALLTYPE(STDMETHODCALLTYPE, QueryInterface, HRESULT(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject));
	MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, AddRef, ULONG());
	MOCK_METHOD0_WITH_CALLTYPE(STDMETHODCALLTYPE, Release, ULONG());
};
