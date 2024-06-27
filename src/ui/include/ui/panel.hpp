#pragma once

#include <cassert>
#include <tl/optional.hpp>
#include <vector>

#include "gfx/color.hpp"
#include "gfx/renderer.hpp"
#include "layout.hpp"
#include "widget.hpp"

namespace ui {
    class ColumnLayout;

    class Panel final : public Widget {
        friend class ColumnLayout;

    private:
        tl::optional<gfx::Color> m_background_color{tl::nullopt};
        std::vector<std::shared_ptr<Widget>> m_widgets;
        std::unique_ptr<Layout> m_layout;

    public:
        Panel(std::unique_ptr<Layout> layout)
            : m_layout{std::move(layout)} {}

        void set_background_color(gfx::Color const color) {
            m_background_color = color;
        }

        void clear_background_color() {
            m_background_color = tl::nullopt;
        }

        template<std::convertible_to<std::shared_ptr<Widget>>... Widgets>
        void add_widgets(Widgets&&... widgets) {
            (m_widgets.emplace_back(widgets), ...);
            recalc_layout();
        }

        void recalc_layout() {
            m_layout->recalc(*this);
        }

        void render(gfx::Renderer& renderer) const override {
            if (m_background_color.has_value()) {
                renderer.draw_rect_filled(area(), m_background_color.value());
            }

            for (auto const& widget : m_widgets) {
                widget->render(renderer);
            }
        }

        tl::optional<Widget const&> find_widget(std::string_view id) const override {
            if (auto const found = Widget::find_widget(id)) {
                return found;
            }

            for (auto const& widget : m_widgets) {
                if (auto const found = widget->find_widget(id)) {
                    return found.value();
                }
            }

            return tl::nullopt;
        }

        tl::optional<Widget&> find_widget(std::string_view id) override {
            if (auto const found = Widget::find_widget(id)) {
                return found;
            }

            for (auto const& widget : m_widgets) {
                if (auto found = widget->find_widget(id)) {
                    return found.value();
                }
            }

            return tl::nullopt;
        }
    };
}  // namespace ui
