#pragma once

using namespace winrt;

using namespace Windows;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;

class App : public implements<App, IFrameworkViewSource, IFrameworkView>
{
    CompositionTarget m_target{ nullptr };
    VisualCollection m_visuals{ nullptr };
    Visual m_selected{ nullptr };
    float2 m_offset{};

public:
    IFrameworkView CreateView();
    void Initialize(CoreApplicationView const&);
    void Load(hstring const&);
    void Uninitialize();
    void Run();
    void SetWindow(CoreWindow const& window);
    void OnPointerPressed(IInspectable const&, PointerEventArgs const& args);
    void OnPointerMoved(IInspectable const&, PointerEventArgs const& args);
    void AddVisual(float2 const point);
};
