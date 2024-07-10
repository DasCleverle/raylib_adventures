#pragma once

#include <tl/optional.hpp>
#include "gfx/renderer.hpp"

namespace ui {
    struct Margin {
        int left;
        int top;
        int right;
        int bottom;

        RectI apply(RectI const rect) const {
            return RectI{
                rect.origin.x + left,
                rect.origin.y + top,
                rect.size.x - left - right,
                rect.size.y - top - bottom,
            };
        }
    };

    class Widget {
    private:
        std::string m_id;
        RectI m_area;
        Margin m_margin{0};

    public:
        Widget(std::string&& id)
            : m_id{std::move(id)} {}

        Widget(Widget const&) = delete;
        Widget& operator=(Widget const&) = delete;
        Widget(Widget&&) = default;
        Widget& operator=(Widget&&) = default;
        virtual ~Widget() = default;

        virtual void render(gfx::Renderer& renderer) const = 0;

        virtual tl::optional<Widget&> find_widget(std::string_view id) {
            if (m_id != id) {
                return tl::nullopt;
            }

            return *this;
        }

        virtual tl::optional<Widget const&> find_widget(std::string_view id) const {
            if (m_id != id) {
                return tl::nullopt;
            }

            return *this;
        }

        [[nodiscard]] std::string_view id() const {
            return m_id;
        }

        [[nodiscard]] RectI area() const {
            return m_area;
        }

        [[nodiscard]] RectI draw_area() const {
            return m_margin.apply(m_area);
        }

        [[nodiscard]] Margin margin() const {
            return m_margin;
        }

        virtual void set_area(RectI const area) {
            m_area = area;
        }

        virtual void set_margin(Margin const margin) {
            m_margin = margin;
        }
    };
}  // namespace ui
