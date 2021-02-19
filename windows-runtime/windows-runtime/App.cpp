#include "pch.h"
#include "App.h"

IFrameworkView App::CreateView()
{
    return *this;
}

void App::Initialize(CoreApplicationView const&)
{
}

void App::Load(hstring const&)
{
}

void App::Uninitialize()
{
}

void App::Run()
{
    CoreWindow window = CoreWindow::GetForCurrentThread();
    window.Activate();

    CoreDispatcher dispatcher = window.Dispatcher();
    dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
}

void App::SetWindow(CoreWindow const& window)
{
    Compositor compositor;
    ContainerVisual root = compositor.CreateContainerVisual();
    m_target = compositor.CreateTargetForCurrentView();
    m_target.Root(root);
    m_visuals = root.Children();

    window.PointerPressed({ this, &App::OnPointerPressed });
    window.PointerMoved({ this, &App::OnPointerMoved });

    window.PointerReleased([&](auto && ...)
    {
        m_selected = nullptr;
    });
}

void App::OnPointerPressed(IInspectable const&, PointerEventArgs const& args)
{
    float2 const point = args.CurrentPoint().Position();

    for (Visual visual : m_visuals)
    {
        float3 const offset = visual.Offset();
        float2 const size = visual.Size();

        if (point.x >= offset.x &&
            point.x < offset.x + size.x &&
            point.y >= offset.y &&
            point.y < offset.y + size.y)
        {
            m_selected = visual;
            m_offset.x = offset.x - point.x;
            m_offset.y = offset.y - point.y;
        }
    }

    if (m_selected)
    {
        m_visuals.Remove(m_selected);
        m_visuals.InsertAtTop(m_selected);
    }
    else
    {
        AddVisual(point);
    }
}

void App::OnPointerMoved(IInspectable const&, PointerEventArgs const& args)
{
    if (m_selected)
    {
        float2 const point = args.CurrentPoint().Position();

        m_selected.Offset(
            {
                point.x + m_offset.x,
                point.y + m_offset.y,
                0.0f
            });
    }
}

void App::AddVisual(float2 const point)
{
    Compositor compositor = m_visuals.Compositor();
    SpriteVisual visual = compositor.CreateSpriteVisual();

    static Color colors[] =
    {
        { 0xDC, 0x5B, 0x9B, 0xD5 },
        { 0xDC, 0xED, 0x7D, 0x31 },
        { 0xDC, 0x70, 0xAD, 0x47 },
        { 0xDC, 0xFF, 0xC0, 0x00 }
    };

    static unsigned last = 0;
    unsigned const next = ++last % _countof(colors);
    visual.Brush(compositor.CreateColorBrush(colors[next]));

    float const BlockSize = 100.0f;

    visual.Size(
        {
            BlockSize,
            BlockSize
        });

    visual.Offset(
        {
            point.x - BlockSize / 2.0f,
            point.y - BlockSize / 2.0f,
            0.0f,
        });

    m_visuals.InsertAtTop(visual);

    m_selected = visual;
    m_offset.x = -BlockSize / 2.0f;
    m_offset.y = -BlockSize / 2.0f;
}
