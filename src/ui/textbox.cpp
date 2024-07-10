#include "ui/textbox.hpp"

#include <raylib.h>
#include <string_view>

#include "ui/event_listener.hpp"
#include "ui/keycode.hpp"
#include "ui/keystate.hpp"
#include "ui/utils.hpp"
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

        renderer.draw_text(*m_font, m_visible_text, text_area().origin, gfx::Colors::Black);

        if (m_is_focused) {
            renderer.draw_line(
                m_cursor_position,
                m_cursor_position + Vec2i{0, m_font->size()},
                2,
                gfx::Colors::Black
            );
        }
    }

    EventListenerResult Textbox::handle(MouseEvent const& event) {
        auto contains = draw_area().contains(event.position);
        auto is_left = event.button == MouseButton::Left;
        auto is_pressed = event.state == KeyState::Pressed;

        if (not contains) {
            if (m_is_focused) {
                m_is_focused = false;
                update();
            }

            return EventListenerResult::Continue;
        }

        if (not is_left) {
            return EventListenerResult::Continue;
        }

        if (not m_is_focused and is_pressed) {
            m_is_focused = true;
            return EventListenerResult::Handled;
        }

        return EventListenerResult::Continue;
    }

    EventListenerResult Textbox::handle(TypedEvent const& event) {
        if (not m_is_focused) {
            return EventListenerResult::Continue;
        }

        m_cursor += insert_utf8_codepoint(m_text, m_cursor, event.utf8_codepoint);
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

                m_cursor -= erase_utf8_codepoint(m_text, m_cursor - 1);
                update();
                break;

            case KeyCode::Delete:
                if (m_cursor == m_text.size()) {
                    break;
                }

                erase_utf8_codepoint(m_text, m_cursor);
                update();
                break;

            case KeyCode::Left:
                if (m_cursor == 0) {
                    break;
                }

                m_cursor = rfind_utf8_boundary(m_text, m_cursor - 1);
                update();
                break;

            case KeyCode::Right:
                if (m_cursor == m_text.size()) {
                    break;
                }

                m_cursor = find_utf8_boundary(m_text, m_cursor + 1);
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

            default:
                break;
        }

        return EventListenerResult::Handled;
    }

    void Textbox::update() {
        auto area = text_area();
        auto size = m_font->measure_text(m_text);

        if (size.x <= area.size.x) {
            m_visible_text = m_text;
            m_visible_cursor = m_cursor;
        }
        else if (not m_is_focused) {
            m_visible_text = m_text;

            while (size.x >= area.size.x) {
                erase_utf8_codepoint(m_visible_text, m_visible_text.size());
                size = m_font->measure_text(m_visible_text);
            }
        }

        auto text_until_cursor = m_visible_text.substr(0, m_visible_cursor);
        auto until_cursor_size = m_font->measure_text(text_until_cursor);

        m_cursor_position = Vec2i{
            area.origin.x + until_cursor_size.x,
            area.origin.y,
        };
    }

    [[nodiscard]] RectI Textbox::text_area() const {
        return Margin{6, 6, 6, 6}.apply(draw_area());
    }

}  // namespace ui
