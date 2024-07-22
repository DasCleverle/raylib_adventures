#pragma once

#include <string>
#include "gfx/render_buffer.hpp"
#include "ui/event.hpp"
#include "ui/event_listener.hpp"
#include "ui/widget.hpp"

namespace ui {

    class Textbox : public Widget, public EventListener<MouseEvent, TypedEvent, KeyboardEvent> {
    private:
        gfx::Font const* m_font;

        bool m_is_focused{false};

        gfx::RenderBuffer m_buffer;
        RectI m_visible_area;

        std::u32string m_text;
        std::size_t m_cursor{};

        std::size_t m_last_cursor{};
        std::size_t m_last_text_length{};
        Vec2i m_last_text_size{};

        gfx::Shader m_selection_shader;

        bool m_is_selecting{false};
        std::optional<std::size_t> m_selection_begin{};
        std::size_t m_selection_length{};

        void update();
        void update_visible_area(Vec2i cursor_position, Vec2i text_size);

        void resize_buffer_if_needed(Vec2i required_size);

        void erase_selection();
        void reset_selection();

        [[nodiscard]] RectI text_area() const;

    public:
        Textbox(std::string&& id, gfx::Font const& font);
        Textbox(gfx::Font const& font);

        Textbox(Textbox const&) = delete;
        Textbox& operator=(Textbox const&) = delete;
        Textbox(Textbox&&) = default;
        Textbox& operator=(Textbox&&) = default;
        ~Textbox() = default;

        void render(gfx::Renderer& renderer) const override;

        void set_area(RectI area) override;

        EventListenerResult handle(MouseEvent const& event) override;

        EventListenerResult handle(TypedEvent const& event) override;

        EventListenerResult handle(KeyboardEvent const& event) override;
    };

}  // namespace ui
