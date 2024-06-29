#pragma once

#include <cassert>
#include <print>
#include <tl/optional.hpp>
#include <vector>

#include "gfx/color.hpp"
#include "gfx/renderer.hpp"
#include "layout.hpp"
#include "ui/event_listener.hpp"
#include "widget.hpp"

namespace ui {
    class ColumnLayout;
    class RowLayout;

    class Panel final : public Widget, public GenericEventListener {
        friend class ColumnLayout;
        friend class RowLayout;

    private:
        tl::optional<gfx::Color> m_background_color{tl::nullopt};
        std::vector<std::unique_ptr<Widget>> m_widgets;
        std::unique_ptr<Layout> m_layout;

        template<typename T>
        void add_widget_core(T&& widget) {
            m_widgets.emplace_back(std::make_unique<std::remove_reference_t<T>>(std::move(widget)));
        }

    public:
        template<std::derived_from<Layout> L>
        Panel(std::string&& id, L&& layout)
            : Widget{std::move(id)}, m_layout{std::make_unique<L>(std::move(layout))} {}

        void set_background_color(gfx::Color const color) {
            m_background_color = color;
        }

        void clear_background_color() {
            m_background_color = tl::nullopt;
        }

        template<class... Widgets>
        requires(std::derived_from<Widgets, Widget> && ...)
        void add_widgets(Widgets&&... widgets) {
            (add_widget_core(std::move(widgets)), ...);
            recalc_layout();
        }

        void recalc_layout() {
            m_layout->recalc(*this);
        }

        void set_area(RectI const area) override {
            Widget::set_area(area);
            recalc_layout();
        }

        void render(gfx::Renderer& renderer) const override {
            if (m_background_color.has_value()) {
                renderer.draw_rect_filled(draw_area(), m_background_color.value());
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

        EventListenerResult handle(Event const& event) override {
            for (auto const& widget : m_widgets) {
                if (auto listener = dynamic_cast<GenericEventListener*>(widget.get())) {
                    auto result = listener->handle(event);

                    if (result == EventListenerResult::Handled) {
                        return EventListenerResult::Handled;
                    }
                }
            }

            return EventListenerResult::Continue;
        }
    };
}  // namespace ui
