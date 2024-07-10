#pragma once

#include <string>
#include "ui/event.hpp"
#include "ui/event_listener.hpp"
#include "ui/widget.hpp"

namespace ui {

    class Textbox : public Widget, public EventListener<MouseEvent, TypedEvent, KeyboardEvent> {
    private:
        bool m_is_focused;
        std::string m_text;
        std::size_t m_cursor{};

        std::size_t m_visible_text_begin;
        std::size_t m_visible_text_size;

        std::string m_visible_text;
        std::size_t m_visible_cursor;
        Vec2i m_cursor_position;

        gfx::Font const* m_font;

        void update();

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

        EventListenerResult handle(MouseEvent const& event) override;

        EventListenerResult handle(TypedEvent const& event) override;

        EventListenerResult handle(KeyboardEvent const& event) override;
    };

}  // namespace ui
