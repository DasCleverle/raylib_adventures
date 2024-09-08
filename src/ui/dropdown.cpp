#include "ui/dropdown.hpp"

#include "ui/column_layout.hpp"
#include "ui/panel.hpp"
#include "ui/utils.hpp"
#include "ui/widget_factory.hpp"

namespace ui {

    DropdownScene::DropdownScene(SceneStack& scene_stack, gfx::Font const& font)
            : m_scene_stack{&scene_stack},
              m_font{&font},
              m_panel{Panel{get_next_id<Panel>("dropdown_panel"), ColumnLayout{1}}} {

        m_panel.set_background_color(gfx::Colors::Gray);
    }

    void DropdownScene::render(gfx::Renderer& renderer) const {
        m_panel.render(renderer);
    }

    EventListenerResult DropdownScene::handle(Event const& event) {
        return std::visit(
            [this](auto& event) {
                using T = std::decay_t<decltype(event)>;

                if constexpr (std::is_same_v<T, MouseEvent>) {
                    if (event.is_contained_left_click(m_panel.area())) {
                        m_panel.handle(event);
                        return EventListenerResult::Handled;
                    }
                    else if (event.state != KeyState::Released) {
                        hide();
                        return EventListenerResult::Handled;
                    }
                }
                else if constexpr (std::is_same_v<T, MouseMoveEvent>) {
                    auto const area = m_panel.area();

                    if (area.contains(event.origin) and area.contains(event.target)) {
                        m_panel.handle(event);
                        return EventListenerResult::Handled;
                    }
                    else if (area.contains(event.origin) or area.contains(event.target)) {
                        m_panel.handle(event);
                        return EventListenerResult::Continue;
                    }
                }
                else if constexpr (std::is_same_v<T, MouseWheelEvent>) {
                    if (m_panel.area().contains(event.position)) {

                        m_panel.handle(event);
                        return EventListenerResult::Handled;
                    }
                }

                return EventListenerResult::Continue;
            },
            event
        );
    }

    void DropdownScene::add_option(std::string_view id, std::string_view text, std::any value) {
        m_options.emplace_back(std::string{id}, std::string{text}, value);
        m_is_dirty = true;
    }

    void DropdownScene::remove_option(std::string_view id) {
        std::erase_if(m_options, [id](DropdownOption option) { return option.id == id; });
        m_is_dirty = true;
    }

    void DropdownScene::clear_options() {
        m_options.clear();
        m_is_dirty = true;
    }

    void DropdownScene::show(Dropdown const& dropdown) {
        if (m_is_opened) {
            return;
        }

        update(dropdown);
        m_scene_stack->push_back(*this);
        m_is_opened = true;
    }

    void DropdownScene::hide() {
        if (not m_is_opened) {
            return;
        }

        m_scene_stack->pop();
        m_is_opened = false;
    }

    void DropdownScene::toggle(Dropdown const& dropdown) {
        if (m_is_opened) {
            hide();
        }
        else {
            show(dropdown);
        }
    }

    void DropdownScene::update(Dropdown const& dropdown) {
        auto const draw_area = dropdown.draw_area();

        m_panel.set_area(RectI{
            draw_area.origin.x,
            draw_area.origin.y + draw_area.size.y,
            draw_area.size.x,
            static_cast<int>(draw_area.size.y * m_options.size())
        });

        if (not m_is_dirty) {
            return;
        }

        std::vector<Label> labels;

        for (auto& option : m_options) {
            labels.emplace_back(std::string{option.text}, *m_font);
        }

        m_panel.clear_widgets();
        m_panel.add_widgets(std::move(labels));

        m_is_dirty = false;
    }

    Dropdown::Dropdown(
        std::string&& id,
        gfx::Font const& font,
        SceneStack& scene_stack,
        EventDispatcher& event_dispatcher
    )
        : Widget{std::move(id)},
          m_label{"", font},
          m_scene{std::make_unique<DropdownScene>(scene_stack, font)},
          m_font{&font},
          m_scene_stack{&scene_stack},
          m_event_dispatcher{&event_dispatcher} {}

    Dropdown::Dropdown(gfx::Font const& font, SceneStack& scene_stack, EventDispatcher& event_dispatcher)
        : Dropdown{get_next_id<Dropdown>("dropdown"), font, scene_stack, event_dispatcher} {}

    void Dropdown::render(gfx::Renderer& renderer) const {
        renderer.draw_rect_filled(draw_area(), gfx::Colors::LightGray);
        m_label.render(renderer);

        auto const chevron_draw_area = chevron_area().scale_from_center(0.5);
        auto const vertex_0 = chevron_draw_area.origin;
        auto const vertex_1 = chevron_draw_area.origin
                              + Vec2i{chevron_draw_area.size.x / 2, chevron_draw_area.size.y};
        auto const vertex_2 = chevron_draw_area.origin + Vec2i{chevron_draw_area.size.x, 0};

        renderer.draw_triangle_filled(vertex_0, vertex_1, vertex_2, gfx::Colors::DarkGray);
    }

    EventListenerResult Dropdown::handle(MouseEvent const& event) {
        if (not event.is_contained_left_click(draw_area())) {
            return EventListenerResult::Continue;
        }

        m_scene->toggle(*this);
        return EventListenerResult::Handled;
    }

    void Dropdown::add_option(std::string_view id, std::string_view text, std::any value) {
        m_scene->add_option(id, text, value);
    }

    void Dropdown::clear_options() {
        m_scene->clear_options();
    }

    void Dropdown::remove_option(std::string_view id) {
        m_scene->remove_option(id);
    }

    void Dropdown::set_area(RectI const area) {
        Widget::set_area(area);
        m_label.set_area(label_area());
    }

    [[nodiscard]] RectI Dropdown::label_area() const {
        auto const area = draw_area();

        return RectI{
            area.origin,
            area.size.x - area.size.y,
            area.size.y,
        };
    }

    [[nodiscard]] RectI Dropdown::chevron_area() const {
        auto const draw = label_area();
        auto const label = label_area();

        return {
            label.origin.x + label.size.x,
            label.origin.y,
            draw.size.y,
            draw.size.y,
        };
    }

}  // namespace ui
