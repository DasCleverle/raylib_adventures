#pragma once

#include <cstdio>

#include "font_type.hpp"
#include "gfx/font_manager.hpp"
#include "gfx/window.hpp"
#include "ui/event_dispatcher.hpp"
#include "ui/panel.hpp"

class MyTestListener;

class Application final {
private:
    gfx::Window m_window;
    gfx::FontManager<FontType> m_font_manager;
    ui::EventDispatcher m_event_dispatcher;

    ui::Panel m_ui_panel;

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
};
