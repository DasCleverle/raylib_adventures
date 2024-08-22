#include "application.hpp"

#include <cstdio>

#include "gfx/font_config.hpp"
#include "ui/button.hpp"
#include "ui/column_layout.hpp"
#include "ui/event.hpp"
#include "ui/row_layout.hpp"
#include "ui/ui_scene.hpp"

static gfx::FontConfig<FontType> s_font_config = {
    {
     {FontType::Bitcell, "assets/fonts/bitcell.ttf", 40},
     {FontType::Roboto, "assets/fonts/roboto.ttf", 40},
     },
    FontType::Roboto
};

class MyTestListener : public ui::EventListener<ui::ClickEvent> {
    ui::EventListenerResult handle(ui::ClickEvent const& event) override {
        std::println("button {} clicked", event.button->id());
        return ui::EventListenerResult::Handled;
    }
};

void add_panel_widgets(Application const& app, ui::Panel& panel) {
    auto textbox = app.widget_factory().create_textbox();
    textbox.set_margin(ui::Margin{10, 10, 10, 10});

    panel.add_widgets(
        app.widget_factory().create_button("Button 1"),
        app.widget_factory().create_button("Button 2"),
        app.widget_factory().create_button("Button 3"),
        app.widget_factory().create_button("Button 4"),
        std::move(textbox)
    );
}

Application::Application()
    : m_window{1600, 900, "My cool game"},
      m_font_manager{s_font_config},
      m_widget_factory{m_event_dispatcher, m_font_manager},
      m_scene_stack{std::make_shared<ui::SceneStack>()} {}

void Application::init() {
    m_window.set_option(gfx::WindowOption::Resizeable, false);
    m_window.set_target_fps(165);

    ui::Panel main_panel{"main_panel", ui::RowLayout(1)};

    // ui::Panel row_panel{"row_panel", ui::RowLayout(1)};
    ui::Panel column_panel{"column_panel", ui::ColumnLayout(1)};

    // add_panel_widgets(*this, row_panel);
    add_panel_widgets(*this, column_panel);

    main_panel.set_area({100, 100, 500, 400});
    main_panel.add_widgets(std::move(column_panel));

    m_scene_stack->emplace_back<ui::UIScene>(std::move(main_panel));
    m_event_dispatcher.listen(m_scene_stack);
}

void Application::update() {
    m_event_dispatcher.update();

    auto renderer = m_window.renderer();

    renderer.clear_background(gfx::Colors::RayWhite);
    renderer.draw_fps({1520, 7});

    m_scene_stack->render(renderer);
}
