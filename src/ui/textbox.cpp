#include "ui/textbox.hpp"

#include <raylib.h>

#include "gfx/color.hpp"
#include "gfx/render_buffer.hpp"
#include "ui/event_listener.hpp"
#include "ui/keycode.hpp"
#include "ui/keystate.hpp"
#include "ui/utils.hpp"
#include "utils/rect.hpp"
#include "utils/strings.hpp"

namespace ui {

    Textbox::Textbox(std::string&& id, gfx::Font const& font)
        : Widget{std::move(id)}, m_font{&font} {}

    Textbox::Textbox(gfx::Font const& font)
        : Widget{get_next_id<Textbox>("textbox")}, m_font{&font} {}

    void Textbox::render(gfx::Renderer& renderer) const {
        auto border_color = m_is_focused ? gfx::Colors::Black : gfx::Colors::DarkGray;

        renderer.draw_rect_filled(draw_area(), gfx::Colors::LightGray);
        renderer.draw_rect_outline(draw_area(), 4, border_color);
        renderer.render_buffer(m_buffer, text_area().origin, m_visible_area);
    }

    EventListenerResult Textbox::handle(MouseEvent const& event) {
        auto contains = draw_area().contains(event.position);
        auto is_left = event.button == MouseButton::Left;
        auto is_pressed = event.state == KeyState::Pressed;

        if (not contains) {
            if (m_is_focused) {
                m_is_focused = false;
                m_visible_area.origin = Vec2i{0, 0};
                update();
            }

            return EventListenerResult::Continue;
        }

        if (not is_left) {
            return EventListenerResult::Continue;
        }

        if (not m_is_focused and is_pressed) {
            m_is_focused = true;
            update();
            return EventListenerResult::Handled;
        }

        return EventListenerResult::Continue;
    }

    EventListenerResult Textbox::handle(TypedEvent const& event) {
        if (not m_is_focused) {
            return EventListenerResult::Continue;
        }

        m_text.insert(m_cursor, 1, event.utf8_codepoint);
        m_cursor++;
        update();

        return EventListenerResult::Continue;
    }

    EventListenerResult Textbox::handle(KeyboardEvent const& event) {
        if (not m_is_focused or event.state == KeyState::Released) {
            return EventListenerResult::Continue;
        }

        if (m_text.empty()) {
            return EventListenerResult::Handled;
        }

        switch (event.code) {
            case KeyCode::Backspace:
                if (m_cursor == 0) {
                    break;
                }

                m_text.erase(m_cursor - 1, 1);
                m_cursor--;
                update();
                break;

            case KeyCode::Delete:
                if (m_cursor == m_text.size()) {
                    break;
                }

                m_text.erase(m_cursor, 1);
                update();
                break;

            case KeyCode::Left:
                if (m_cursor == 0) {
                    break;
                }

                m_cursor--;
                update();
                break;

            case KeyCode::Right:
                if (m_cursor == m_text.size()) {
                    break;
                }

                m_cursor++;
                update();
                break;

            case KeyCode::Home:
                if (m_cursor == 0) {
                    break;
                }

                m_cursor = 0;
                update();
                break;

            case KeyCode::End:
                if (m_cursor == m_text.size()) {
                    break;
                }

                m_cursor = m_text.size();
                update();
                break;

            default:
                break;
        }

        return EventListenerResult::Handled;
    }

    void Textbox::update() {
        auto const cursor_position_end =
            m_font->measure_text(std::u32string_view{m_text.data(), m_cursor});
        auto const cursor_position_start = cursor_position_end.hadamard_product({1, 0});

        m_buffer.render_to([&](gfx::BufferRenderer& renderer) {
            renderer.clear_background(gfx::Colors::Blank);
            renderer.draw_text(*m_font, m_text, {0, 0}, gfx::Colors::Black);

            if (m_is_focused) {
                renderer.draw_line(
                    {std::max(1, cursor_position_start.x), cursor_position_start.y},
                    {std::max(1, cursor_position_end.x), cursor_position_end.y},
                    2,
                    gfx::Colors::Black
                );
            }
        });

        auto const text_size = m_font->measure_text(m_text);

        resize_buffer_if_needed({text_size.x, text_area().size.y});
        update_visible_area(cursor_position_start, text_size);

        m_last_cursor = m_cursor;
        m_last_text_length = m_text.size();
        m_last_text_size = text_size;
    }

    void Textbox::update_visible_area(Vec2i const cursor_position, Vec2i const text_size) {
        auto const area = text_area();
        auto const fits_in_text_area = text_size.x <= area.size.x;

        if (fits_in_text_area) {
            m_visible_area = RectI{
                Vec2i{0, 0},
                area.size
            };

            return;
        }

        if (m_cursor == m_last_cursor) {
            return;
        }

        auto const deleted_chars = m_last_text_length > m_text.size();
        auto const moved_right = m_cursor > m_last_cursor;
        auto const visible_cursor_x = cursor_position.x - m_visible_area.origin.x;

        if (deleted_chars and not moved_right) {
            m_visible_area.origin.x -= m_last_text_size.x - text_size.x;
            return;
        }

        // clang-format off
        auto const moved_inside_visible_area = moved_right
            ? visible_cursor_x <= area.size.x
            : visible_cursor_x >= 0;

        if (moved_inside_visible_area) {
            return;
        }

        auto const new_x = moved_right
            ? cursor_position.x - m_visible_area.size.x + 2
            : std::max(0, cursor_position.x - 2);
        // clang-format on

        m_visible_area.origin.x = new_x;
    }

    [[nodiscard]] RectI Textbox::text_area() const {
        return Margin{6, 6, 6, 6}.apply(draw_area());
    }

    void Textbox::set_area(RectI const area) {
        Widget::set_area(area);
        resize_buffer_if_needed(text_area().size);
        update();
    }

    void Textbox::resize_buffer_if_needed(Vec2i required_size) {
        if (m_buffer.size().x >= required_size.x and m_buffer.size().y >= required_size.y) {
            return;
        }

        m_buffer.resize(required_size + Vec2i{text_area().size.x, 0});
    }

}  // namespace ui
