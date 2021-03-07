#include "pch.h"
#include "TexturedRectanglePainter.h"

D3D11_INPUT_ELEMENT_DESC input_elements[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

struct Vertex
{
	float X, Y, Z;
	float U, V;
};

Vertex OurVertices[] =
{
	{ 0.0f, 0.5f, 0.0f, 0.5f, 1.0f },
	{ 0.45f, -0.5f, 0.0f, 1.0f, 0.0f },
	{ -0.45f, -0.5f, 0.0f, 0.0f, 0.0f },
};

TexturedRectanglePainter::TexturedRectanglePainter(
	GraphicsDeviceProvider& device_provider, 
	GraphicsResourceFactory& resource_factory
) :
	device_provider_(device_provider),
	resource_factory_(resource_factory)
{
}

winrt::Windows::Foundation::IAsyncAction TexturedRectanglePainter::CreateResources()
{
	sampler_state_ = nullptr;
	vertex_buffer_ = nullptr;
	vertex_shader_ = nullptr;
	input_layout_ = nullptr;
	pixel_shader_ = nullptr;
	texture_ = nullptr;

	resource_factory_.CreateSamplerState(sampler_state_.put());
	resource_factory_.CreateVertexBuffer(vertex_buffer_.put(), sizeof(Vertex) * ARRAYSIZE(OurVertices), OurVertices);

	std::vector<winrt::Windows::Foundation::IAsyncAction> tasks{
		resource_factory_.CreateVertexShader(
			L"TexturedTriangleVertexShader.cso",
			input_elements,
			ARRAYSIZE(input_elements),
			vertex_shader_.put(),
			input_layout_.put()
		),
		resource_factory_.CreatePixelShader(
			L"TexturedTrianglePixelShader.cso",
			pixel_shader_.put()
		),
		resource_factory_.CreateTexture(
			L"Assets\\LockScreenLogo.scale-200.png",
			nullptr,
			texture_.put()
		),
	};

	for (auto&& task : tasks) {
		co_await task;
	}
}

void TexturedRectanglePainter::Paint()
{
	auto context = device_provider_.GetContext();

	ID3D11ShaderResourceView* texture = texture_.get();
	context->PSSetShaderResources(0, 1, &texture);

	context->VSSetShader(vertex_shader_.get(), nullptr, 0);
	context->PSSetShader(pixel_shader_.get(), nullptr, 0);
	context->IASetInputLayout(input_layout_.get());

	ID3D11SamplerState* sampler_state{ sampler_state_.get() };
	context->PSSetSamplers(0, 1, &sampler_state);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ID3D11Buffer* vertex_buffer{ vertex_buffer_.get() };
	context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->Draw(3, 0);
}
