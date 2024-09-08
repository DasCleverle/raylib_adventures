#pragma once

#include <cstdio>

#include "font_type.hpp"
#include "gfx/font_manager.hpp"
#include "gfx/window.hpp"
#include "ui/event_dispatcher.hpp"
#include "ui/scene_stack.hpp"
#include "ui/widget_factory.hpp"

class Application final {
private:
    gfx::Window m_window;
    gfx::FontManager<FontType> m_font_manager;
    ui::EventDispatcher m_event_dispatcher;
    std::shared_ptr<ui::SceneStack> m_scene_stack;
    ui::WidgetFactory m_widget_factory;

    void update();
    void init();

public:
    Application();

    void run() {
        init();

        while (not m_window.should_close()) {
            update();
        }
    }

    ui::WidgetFactory const& widget_factory() const {
        return m_widget_factory;
    }
};
