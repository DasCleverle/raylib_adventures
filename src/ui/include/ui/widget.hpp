#pragma once

#include <tl/optional.hpp>
#include "gfx/renderer.hpp"

namespace ui {
    class Widget {
    private:
        RectI m_area;
        std::string m_id;

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

        virtual void set_area(RectI const area) {
            m_area = area;
        }
    };
}  // namespace ui
