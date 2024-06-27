#pragma once

#include "gfx/renderer.hpp"

namespace ui {
    class Widget {
    private:
        RectI m_area;

    public:
        Widget() = default;

        Widget(Widget const&) = delete;
        Widget& operator=(Widget const&) = delete;
        Widget(Widget&&) = default;
        Widget& operator=(Widget&&) = default;
        virtual ~Widget() = default;

        virtual void render(gfx::Renderer& renderer) const = 0;

        [[nodiscard]] RectI area() const {
            return m_area;
        }

        virtual void set_area(RectI const area) {
            m_area = area;
        }
    };
}  // namespace ui
