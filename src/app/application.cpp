#include "application.hpp"

#include <cstdio>
#include <memory>

#include "gfx/font_config.hpp"
#include "ui/button.hpp"
#include "ui/column_layout.hpp"
#include "ui/event.hpp"

static gfx::FontConfig<FontType> s_font_config = {
    {{FontType::Bitcell, "assets/fonts/bitcell.ttf", 40}},
    FontType::Bitcell
};

template<typename T>
struct NoopDeleter {
    void operator()(T*) {}
};

class MyTestListener : public ui::EventListener<ui::ClickEvent> {
    ui::EventListenerResult handle(ui::ClickEvent const& event) override {
        std::println("button {} clicked", event.button->id());
        return ui::EventListenerResult::Handled;
    }
};

Application::Application()
    : m_window{1600, 900, "My cool game"},
      m_font_manager{s_font_config},
      m_ui_panel{"main_panel", ui::ColumnLayout(3)},
      m_widget_factory{m_event_dispatcher, m_font_manager} {}

void Application::init() {
    m_window.set_option(gfx::WindowOption::Resizeable, false);
    m_window.set_target_fps(60);

    auto const& font = m_font_manager.default_font();

    auto button = m_widget_factory.create_button("Okay");
    button.listen(std::make_shared<MyTestListener>());

    m_ui_panel.set_background_color(gfx::Colors::LightGray);
    m_ui_panel.set_area({50, 50, 603, 603});
    m_ui_panel.add_widgets(std::move(button));

    m_event_dispatcher.listen(std::shared_ptr<ui::Panel>{&m_ui_panel, NoopDeleter<ui::Panel>{}});
}

void Application::update() {
    m_event_dispatcher.update();

    auto renderer = m_window.renderer();

    renderer.clear_background(gfx::Colors::RayWhite);
    renderer.draw_fps({1520, 7});

    m_ui_panel.render(renderer);
}
