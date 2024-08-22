#include "ui/textbox.hpp"

#include <optional>
#include <string_view>

#include "gfx/color.hpp"
#include "gfx/render_buffer.hpp"
#include "gfx/shader.hpp"
#include "ui/event_listener.hpp"
#include "ui/keycode.hpp"
#include "ui/keystate.hpp"
#include "ui/utils.hpp"
#include "utils/rect.hpp"
#include "utils/strings.hpp"

static constexpr char const* s_selection_vertex_shader_code = R"(
    #version 330

    in vec3 vertexPosition;
    in vec2 vertexTexCoord;
    in vec4 vertexColor;

    out vec3 fragPosition;
    out vec2 fragTexCoord;
    out vec4 fragColor;

    uniform mat4 mvp;

    void main() {
        fragPosition = vertexPosition;
        fragTexCoord = vertexTexCoord;
        fragColor = vertexColor;

        gl_Position = mvp * vec4(vertexPosition, 1.0);;
    }
)";

static constexpr char const* s_selection_fragment_shader_code = R"(
    #version 330

    in vec3 fragPosition;
    in vec2 fragTexCoord;
    in vec4 fragColor;

    uniform vec2 selectionOrigin;
    uniform vec2 selectionSize;
    uniform sampler2D texture0;

    out vec4 finalColor;

    bool contains(vec2 origin, vec2 size, vec3 position) {
        return position.x >= origin.x
            && position.y >= origin.y
            && position.x <= origin.x + size.x
            && position.y <= origin.y + size.y;
    }

    void main() {
        vec4 texColor = texture(texture0, fragTexCoord);

        if (contains(selectionOrigin, selectionSize, fragPosition)) {
            finalColor = vec4(1.0 - fragColor.rgb, fragColor.a) * texColor;
        }
        else {
            finalColor = fragColor * texColor;
        }
    }
)";

namespace ui {

    Textbox::Textbox(std::string&& id, gfx::Font const& font)
        : Widget{std::move(id)},
          m_font{&font},
          m_selection_shader{gfx::Shader::from_memory(
              s_selection_vertex_shader_code,
              s_selection_fragment_shader_code
          )} {}

    Textbox::Textbox(gfx::Font const& font)
        : Textbox{get_next_id<Textbox>("textbox"), font} {}

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

        if (not contains and is_pressed) {
            if (m_is_focused) {
                m_is_focused = false;
                m_visible_area.origin = Vec2i{0, 0};
                m_is_selecting = false;
                reset_selection();

                update();
            }

            return EventListenerResult::Continue;
        }

        if (not is_left) {
            return EventListenerResult::Continue;
        }

        if (is_pressed) {
            if (not m_is_focused) {
                m_is_focused = true;
            }

            auto const index = position_to_text_index(event.position);

            if (m_is_selecting) {
                set_selection(m_cursor, index);
            }
            else {
                reset_selection();
                m_cursor = index;
                m_is_selecting = true;
            }

            update();

            return EventListenerResult::Handled;
        }
        else if (not m_is_shift_pressed) {
            m_is_selecting = false;
        }

        return EventListenerResult::Continue;
    }

    EventListenerResult Textbox::handle(MouseMoveEvent const& event) {
        auto contains_origin = draw_area().contains(event.origin);
        auto contains_target = draw_area().contains(event.target);

        if (contains_origin and not contains_target and m_prev_mouse_cursor.has_value()) {
            Mouse::set_cursor(m_prev_mouse_cursor.value());
            m_prev_mouse_cursor = std::nullopt;
        }
        else if (contains_target and Mouse::current_cursor() != MouseCursor::IBeam) {
            m_prev_mouse_cursor = Mouse::current_cursor();
            Mouse::set_cursor(MouseCursor::IBeam);
        }

        if (m_is_selecting) {
            auto const index = position_to_text_index(event.target);
            set_selection(m_cursor, index);
            update();
        }

        return EventListenerResult::Continue;
    }

    EventListenerResult Textbox::handle(TypedEvent const& event) {
        if (not m_is_focused) {
            return EventListenerResult::Continue;
        }

        erase_selection();
        m_text.insert(m_cursor, 1, event.utf8_codepoint);
        m_cursor++;
        update();

        return EventListenerResult::Handled;
    }

    EventListenerResult Textbox::handle(KeyboardEvent const& event) {
        if (event.code == KeyCode::LeftShift or event.code == KeyCode::RightShift) {
            m_is_selecting = event.state == KeyState::Pressed;
            m_is_shift_pressed = m_is_selecting;
            return EventListenerResult::Continue;
        }

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

                if (m_selection_begin.has_value()) {
                    erase_selection();
                }
                else {
                    m_text.erase(m_cursor - 1, 1);
                    m_cursor--;
                }

                update();
                break;

            case KeyCode::Delete:
                if (m_cursor == m_text.size()) {
                    break;
                }

                if (m_selection_begin.has_value()) {
                    erase_selection();
                }
                else {
                    m_text.erase(m_cursor, 1);
                }

                update();
                break;

            case KeyCode::Left:
                if (m_cursor == 0) {
                    break;
                }

                m_cursor--;

                if (m_is_selecting) {
                    if (not m_selection_begin.has_value()) {
                        m_selection_begin = m_cursor;
                        m_selection_length = 1;
                    }
                    else if (m_cursor < m_selection_begin) {
                        m_selection_begin = m_cursor;
                        m_selection_length++;
                    }
                    else if (m_cursor > m_selection_begin) {
                        m_selection_length--;
                    }
                    else {
                        reset_selection();
                    }
                }
                else {
                    reset_selection();
                }

                update();
                break;

            case KeyCode::Right:
                if (m_cursor == m_text.size()) {
                    break;
                }

                m_cursor++;

                if (m_is_selecting) {
                    if (not m_selection_begin.has_value()) {
                        m_selection_begin = m_cursor - 1;
                        m_selection_length = 1;
                    }
                    else if (m_cursor - 1 == m_selection_begin and m_selection_length > 0) {
                        m_selection_begin.value()++;
                        m_selection_length--;
                    }
                    else if (m_cursor - 1 == m_selection_begin and m_selection_length == 0) {
                        m_selection_begin = m_cursor - 1;
                        m_selection_length = 1;
                    }
                    else if (m_cursor > m_selection_begin) {
                        m_selection_length++;
                    }
                    else {
                        reset_selection();
                    }
                }
                else {
                    reset_selection();
                }

                update();
                break;

            case KeyCode::Home:
                if (m_cursor == 0) {
                    break;
                }

                if (m_is_selecting) {
                    if (not m_selection_begin.has_value()) {
                        m_selection_length = m_cursor;
                        m_selection_begin = 0;
                    }
                    else if (m_cursor == m_selection_begin) {
                        m_selection_length += m_selection_begin.value();
                        m_selection_begin = 0;
                    }
                    else if (m_cursor > m_selection_begin) {
                        m_selection_length = m_selection_begin.value();
                        m_selection_begin = 0;
                    }
                }
                else {
                    reset_selection();
                }

                m_cursor = 0;

                update();
                break;

            case KeyCode::End:
                if (m_cursor == m_text.size()) {
                    break;
                }

                if (m_is_selecting) {
                    if (not m_selection_begin.has_value()) {
                        m_selection_length = m_text.size() - m_cursor;
                        m_selection_begin = m_cursor;
                    }
                    else if (m_cursor == m_selection_begin) {
                        m_selection_begin = m_cursor + m_selection_length;
                        m_selection_length = m_text.size() - m_selection_begin.value();
                    }
                    else if (m_cursor > m_selection_begin) {
                        m_selection_length += m_text.size() - m_selection_begin.value() - 1;
                    }
                }
                else {
                    reset_selection();
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
        auto const text_until_cursor = std::u32string_view{m_text.data(), m_cursor};
        auto const cursor_position_end = m_font->measure_text(text_until_cursor);
        auto const cursor_position_start = cursor_position_end.hadamard_product({1, 0});

        m_buffer.render_to([&](gfx::BufferRenderer& renderer) {
            renderer.clear_background(gfx::Colors::Blank);

            if (m_selection_begin.has_value()) {
                auto const until_selection_begin = m_font->measure_text(
                    std::u32string_view{m_text.data(), m_selection_begin.value()}
                );
                auto const selection_size = m_font->measure_text(std::u32string_view{
                    m_text.begin() + m_selection_begin.value(),
                    m_text.begin() + m_selection_begin.value() + m_selection_length
                });

                RectF selected_area{
                    Vec2f{until_selection_begin.x, 0},
                    Vec2f{selection_size}
                };

                m_selection_shader.set_value("selectionOrigin", selected_area.origin);
                m_selection_shader.set_value("selectionSize", selected_area.size);

                renderer.draw_rect_filled(selected_area, gfx::Colors::Black);

                renderer.with_shader(m_selection_shader, [&](auto& shaded) {
                    shaded.draw_text(*m_font, m_text, {0, 0}, gfx::Colors::Black);
                });
            }
            else {
                renderer.draw_text(*m_font, m_text, {0, 0}, gfx::Colors::Black);
            }

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

    [[nodiscard]] std::size_t Textbox::position_to_text_index(Vec2i const position) const {
        auto const relative_position = position - text_area().origin;
        auto text_size = m_font->measure_text(m_text);

        if (text_size.x <= relative_position.x) {
            return m_text.size();
        }
        else {
            for (std::size_t i = m_text.size(); i > 0; i--) {
                std::u32string_view text{m_text.data(), i};
                text_size = m_font->measure_text(text);

                std::u32string_view last_char{m_text.data() + i, 1};
                auto const last_char_size = m_font->measure_text(last_char);

                if (text_size.x <= relative_position.x + last_char_size.x / 2) {
                    return i;
                }
            }
        }

        return 0;
    }

    void Textbox::set_area(RectI const area) {
        Widget::set_area(area);
        resize_buffer_if_needed(text_area().size);
        update();
    }

    void Textbox::resize_buffer_if_needed(Vec2i const required_size) {
        if (m_buffer.size().x >= required_size.x and m_buffer.size().y >= required_size.y) {
            return;
        }

        m_buffer.resize(required_size + Vec2i{text_area().size.x, 0});
    }

    void Textbox::set_selection(std::size_t begin_index, std::size_t end_index) {
        if (begin_index == end_index) {
            reset_selection();
            return;
        }

        if (begin_index > end_index) {
            std::swap(begin_index, end_index);
        }

        auto const length = end_index - begin_index;

        m_selection_begin = begin_index;
        m_selection_length = length;
    }

    void Textbox::erase_selection() {
        if (not m_selection_begin.has_value()) {
            return;
        }

        m_text.erase(m_selection_begin.value(), m_selection_length);
        m_cursor = m_selection_begin.value();

        reset_selection();
    }

    void Textbox::reset_selection() {
        m_selection_begin = std::nullopt;
        m_selection_length = 0;
    }

}  // namespace ui
