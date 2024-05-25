#pragma once

#include <cstdio>

#include "font_type.hpp"
#include "gfx/font_manager.hpp"
#include "gfx/window.hpp"
#include "ui/event_dispatcher.hpp"

class MyTestListener;

class Application final {
private:
    gfx::Window m_window;
    gfx::FontManager<FontType> m_font_manager;
    ui::EventDispatcher m_event_dispatcher;

    std::shared_ptr<MyTestListener> m_my_test_listener;

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
