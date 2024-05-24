#include "application.hpp"

#include <cstdio>
#include <memory>

#include "gfx/color.hpp"
#include "gfx/renderer.hpp"
#include "ui/event.hpp"

class MyTestListener : public ui::EventListener<ui::KeyboardEvent> {
    ui::EventListenerResult handle(ui::KeyboardEvent const& event) override {
        printf(
            "handling key board event %d, type %d\n",
            static_cast<int>(event.code),
            static_cast<int>(event.state)
        );

        return ui::EventListenerResult::Handled;
    }
};

static gfx::FontConfig<FontType> s_font_config = {
    { { FontType::Bitcell, "assets/fonts/bitcell.ttf", 40 } },
    FontType::Bitcell
};

Application::Application()
    : m_window{ 1600, 900, "My cool game" },
      m_font_manager{ s_font_config },
      m_my_test_listener{ std::make_shared<MyTestListener>() } {}

void Application::init() {
    m_window.set_option(gfx::WindowOption::Resizeable, false);
    m_window.set_target_fps(60);

    auto listener = std::make_shared<MyTestListener>();
    m_event_dispatcher.listen<ui::KeyboardEvent>(listener);
}

void Application::update() {
    m_event_dispatcher.poll();

    auto renderer = m_window.renderer();

    renderer.clear_background(gfx::Colors::Gray);

    char const* const text = "Hello from RAII renderer";
    Vec2f const text_size = m_font_manager.default_font().measure_text(text);

    renderer.draw_fps({ 1520, 7 });

    renderer.draw_rect_filled(
        { 95, 95, text_size.x + 10, text_size.y + 5 },
        gfx::Colors::SkyBlue
    );
    renderer.draw_rect_outline(
        { 95, 95, text_size.x + 10, text_size.y + 5 },
        3,
        gfx::Colors::Black
    );

    renderer.draw_text(
        m_font_manager.default_font(),
        text,
        { 100, 100 },
        gfx::Colors::White
    );
    renderer.draw_circle_filled({ 600, 200 }, 130, gfx::Colors::White);
}
