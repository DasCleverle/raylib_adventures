#include "application.hpp"

#include <cstdio>
#include <memory>

#include "gfx/font_config.hpp"
#include "ui/button.hpp"
#include "ui/column_layout.hpp"
#include "ui/event.hpp"
#include "ui/label.hpp"

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
    FontType::Roboto
};

Application::Application()
    : m_window{1600, 900, "My cool game"}, m_font_manager{s_font_config} {}

void Application::init() {
    m_window.set_option(gfx::WindowOption::Resizeable, false);
    m_window.set_target_fps(60);

    auto const& font = m_font_manager.default_font();

    m_ui_panel = std::make_unique<ui::Panel>(std::make_unique<ui::ColumnLayout>(3));
    m_ui_panel->set_background_color(gfx::Colors::LightGray);
    m_ui_panel->set_area({50, 50, 603, 603});
    m_ui_panel->add_widgets(
        std::make_shared<ui::Button>("LightGray", font, gfx::Colors::LightGray, m_event_dispatcher),
        std::make_shared<ui::Button>("Gray", font, gfx::Colors::Gray, m_event_dispatcher),
        std::make_shared<ui::Button>("DarkGray", font, gfx::Colors::DarkGray, m_event_dispatcher),
        std::make_shared<ui::Button>("Yellow", font, gfx::Colors::Yellow, m_event_dispatcher),
        std::make_shared<ui::Button>("Gold", font, gfx::Colors::Gold, m_event_dispatcher),
        std::make_shared<ui::Button>("Orange", font, gfx::Colors::Orange, m_event_dispatcher),
        std::make_shared<ui::Button>("Pink", font, gfx::Colors::Pink, m_event_dispatcher),
        std::make_shared<ui::Button>("Red", font, gfx::Colors::Red, m_event_dispatcher),
        std::make_shared<ui::Button>("Maroon", font, gfx::Colors::Maroon, m_event_dispatcher),
        std::make_shared<ui::Button>("Green", font, gfx::Colors::Green, m_event_dispatcher),
        std::make_shared<ui::Button>("Lime", font, gfx::Colors::Lime, m_event_dispatcher),
        std::make_shared<ui::Button>("DarkGreen", font, gfx::Colors::DarkGreen, m_event_dispatcher),
        std::make_shared<ui::Button>("SkyBlue", font, gfx::Colors::SkyBlue, m_event_dispatcher),
        std::make_shared<ui::Button>("Blue", font, gfx::Colors::Blue, m_event_dispatcher),
        std::make_shared<ui::Button>("DarkBlue", font, gfx::Colors::DarkBlue, m_event_dispatcher),
        std::make_shared<ui::Button>("Purple", font, gfx::Colors::Purple, m_event_dispatcher),
        std::make_shared<ui::Button>("Violet", font, gfx::Colors::Violet, m_event_dispatcher),
        std::make_shared<ui::Button>("DarkPurple", font, gfx::Colors::DarkPurple, m_event_dispatcher),
        std::make_shared<ui::Button>("Beige", font, gfx::Colors::Beige, m_event_dispatcher),
        std::make_shared<ui::Button>("Brown", font, gfx::Colors::Brown, m_event_dispatcher),
        std::make_shared<ui::Button>("DarkBrown", font, gfx::Colors::DarkBrown, m_event_dispatcher),
        std::make_shared<ui::Button>("White", font, gfx::Colors::White, m_event_dispatcher),
        std::make_shared<ui::Button>("Black", font, gfx::Colors::Black, m_event_dispatcher),
        std::make_shared<ui::Button>("Blank", font, gfx::Colors::Blank, m_event_dispatcher),
        std::make_shared<ui::Button>("Magenta", font, gfx::Colors::Magenta, m_event_dispatcher),
        std::make_shared<ui::Button>("RayWhite", font, gfx::Colors::RayWhite, m_event_dispatcher)
    );
}

void Application::update() {
    m_event_dispatcher.poll();

    auto renderer = m_window.renderer();

    renderer.clear_background(gfx::Colors::RayWhite);
    renderer.draw_fps({1520, 7});

    m_ui_panel->render(renderer);

    // char const* const text = "Hello from RAII renderer";
    // Vec2f const text_size = m_font_manager.default_font().measure_text(text);
    //
    // renderer.draw_rect_filled({95, 95, text_size.x + 10, text_size.y + 5}, gfx::Colors::SkyBlue);
    // renderer.draw_rect_outline({95, 95, text_size.x + 10, text_size.y + 5}, 3, gfx::Colors::Black);
    //
    // renderer.draw_text(m_font_manager.default_font(), text, {100, 100}, gfx::Colors::White);
    // renderer.draw_circle_filled({600, 200}, 130, gfx::Colors::White);
    //
    // my_label->render(renderer);
}
