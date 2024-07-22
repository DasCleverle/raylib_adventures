#include "ui/mouse.hpp"

#include <raylib.h>
#include <utility>

namespace ui {

    static MouseCursor s_current_cursor = MouseCursor::Default;

    void Mouse::set_cursor(MouseCursor cursor) {
        s_current_cursor = cursor;
        SetMouseCursor(std::to_underlying(cursor));
    }

    MouseCursor Mouse::current_cursor() {
        return s_current_cursor;
    }

}  // namespace ui
