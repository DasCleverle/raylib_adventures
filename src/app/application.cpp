#include "application.hpp"

#include <cstdio>
#include <memory>

#include "gfx/font_config.hpp"
#include "ui/button.hpp"
#include "ui/column_layout.hpp"
#include "ui/event.hpp"
#include "ui/row_layout.hpp"

static gfx::FontConfig<FontType> s_font_config = {
    {{FontType::Bitcell, "assets/fonts/bitcell.ttf", 40}},
    FontType::Bitcell
};

class MyTestListener : public ui::EventListener<ui::ClickEvent> {
    ui::EventListenerResult handle(ui::ClickEvent const& event) override {
        std::println("button {} clicked", event.button->id());
        return ui::EventListenerResult::Handled;
    }
};

void add_panel_widgets(Application const& app, ui::Panel& panel) {
    auto checkbox = app.widget_factory().create_checkbox("Checkbox 1");
    checkbox.set_margin(ui::Margin{10, 10, 10, 10});

    panel.add_widgets(
        app.widget_factory().create_button("Button 1"),
        app.widget_factory().create_button("Button 2"),
        app.widget_factory().create_button("Button 3"),
        app.widget_factory().create_button("Button 4"),
        app.widget_factory().create_button("Button 5"),
        app.widget_factory().create_button("Button 6"),
        app.widget_factory().create_button("Button 7"),
        std::move(checkbox)
    );
}

Application::Application()
    : m_window{1600, 900, "My cool game"},
      m_font_manager{s_font_config},
      m_ui_panel{std::make_shared<ui::Panel>("main_panel", ui::RowLayout(1))},
      m_widget_factory{m_event_dispatcher, m_font_manager} {}

void Application::init() {
    m_window.set_option(gfx::WindowOption::Resizeable, false);
    m_window.set_target_fps(60);

    ui::Panel row_panel{"row_panel", ui::RowLayout(1)};
    ui::Panel column_panel{"column_panel", ui::ColumnLayout(1)};

    add_panel_widgets(*this, row_panel);
    add_panel_widgets(*this, column_panel);

    m_ui_panel->set_area({0, 0, 1600, 900});
    m_ui_panel->add_widgets(std::move(row_panel), std::move(column_panel));

    m_event_dispatcher.listen(m_ui_panel);
}

void Application::update() {
    m_event_dispatcher.update();

    auto renderer = m_window.renderer();

    renderer.clear_background(gfx::Colors::RayWhite);
    renderer.draw_fps({1520, 7});

    m_ui_panel->render(renderer);
}
