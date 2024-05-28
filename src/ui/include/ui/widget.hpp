#pragma once

#include "gfx/renderer.hpp"

namespace ui {
    class Widget {
    private:
        RectF m_area;

    public:
        Widget() = default;
        Widget(Widget const&) = delete;
        Widget(Widget&&) = default;
        Widget& operator=(Widget const&) = delete;
        Widget& operator=(Widget&&) = default;
        virtual ~Widget() = default;

        virtual void render(gfx::Renderer& renderer) const = 0;

        [[nodiscard]] RectF area() const {
            return m_area;
        }

        virtual void set_area(RectF area) {
            m_area = area;
        }
    };
}  // namespace ui
