#include "application.hpp"

#include <cstdio>

#include "gfx/font_config.hpp"
#include "ui/button.hpp"
#include "ui/column_layout.hpp"
#include "ui/event.hpp"

class MyTestListener : public ui::EventListener<ui::KeyboardEvent>,
                       public ui::EventListener<ui::MouseEvent>,
                       public ui::EventListener<ui::MouseMoveEvent>,
                       public ui::EventListener<ui::MouseWheelEvent> {
    ui::EventListenerResult handle(ui::KeyboardEvent const& event) override {
        printf(
            "handling key board event %d, type %d\n",
            static_cast<int>(event.code),
            static_cast<int>(event.state)
        );

        return ui::EventListenerResult::Handled;
    }

    ui::EventListenerResult handle(ui::MouseEvent const& event) override {
        printf(
            "handling mouse button event %d, type %d\n",
            static_cast<int>(event.button),
            static_cast<int>(event.state)
        );

        return ui::EventListenerResult::Handled;
    }

    ui::EventListenerResult handle(ui::MouseMoveEvent const& event) override {
        printf(
            "handling mouse move event from %d,%d to %d,%d (delta %d,%d)\n",
            event.origin.x,
            event.origin.y,
            event.target.x,
            event.target.y,
            event.delta.x,
            event.delta.y
        );

        return ui::EventListenerResult::Handled;
    }

    ui::EventListenerResult handle(ui::MouseWheelEvent const& event) override {
        printf("handling mouse wheel event, direction: %d, %d \n", event.delta.x, event.delta.y);

        return ui::EventListenerResult::Handled;
    }
};

static gfx::FontConfig<FontType> s_font_config = {
    {{FontType::Bitcell, "assets/fonts/bitcell.ttf", 40}},
    FontType::Bitcell
};

Application::Application()
    : m_window{1600, 900, "My cool game"},
      m_font_manager{s_font_config},
      m_ui_panel{"main_panel", ui::ColumnLayout(3)} {}

void Application::init() {
    m_window.set_option(gfx::WindowOption::Resizeable, false);
    m_window.set_target_fps(60);

    auto const& font = m_font_manager.default_font();

    m_ui_panel.set_background_color(gfx::Colors::LightGray);
    m_ui_panel.set_area({50, 50, 603, 603});
    m_ui_panel.add_widgets(ui::Button{"Okay", font});

    m_event_dispatcher.listen(m_ui_panel);
}

void Application::update() {
    m_event_dispatcher.update();

    auto renderer = m_window.renderer();

    renderer.clear_background(gfx::Colors::RayWhite);
    renderer.draw_fps({1520, 7});

    m_ui_panel.render(renderer);
}
