#include "pch.h"
#include "ViewImpl.h"

ViewImpl::ViewImpl(
	GraphicsDeviceContainer& device_container, 
	DoubleBuffer& double_buffer, 
	std::vector<std::shared_ptr<Painter>> painters
) :
	device_container_(device_container),
	double_buffer_(double_buffer),
	painters_(painters),
	ready_(false)
{
}

void ViewImpl::OnInitialize()
{
	device_container_.Create();
}

void ViewImpl::OnSetWindow(winrt::Windows::UI::Core::CoreWindow const* window)
{
	double_buffer_.SetWindow(window);
	double_buffer_.Create();
}

void ViewImpl::OnLoad()
{
	CreatePainterResources();
}

void ViewImpl::OnSuspending()
{
	device_container_.Trim();
}

void ViewImpl::OnResize()
{
	bool success = double_buffer_.Create();

	if (!success) {
		HandleDeviceLost();
	}
}

void ViewImpl::Paint()
{
	double_buffer_.StartFrame();

	if (ready_) {
		InvokePainters();
	}

	bool success = double_buffer_.FinishFrame();

	if (!success) {
		HandleDeviceLost();
	}
}

winrt::fire_and_forget ViewImpl::CreatePainterResources()
{
	ready_ = false;

	std::vector<winrt::Windows::Foundation::IAsyncAction> tasks;

	for (auto&& painter : painters_) {
		tasks.push_back(painter->CreateResources());
	}

	for (auto&& task : tasks) {
		co_await task;
	}

	ready_ = true;
}

void ViewImpl::InvokePainters()
{
	for (auto&& painter : painters_) {
		painter->Paint();
	}
}

void ViewImpl::HandleDeviceLost()
{
	double_buffer_.Destroy();
	device_container_.Create();
	double_buffer_.Create();
	CreatePainterResources();
}
