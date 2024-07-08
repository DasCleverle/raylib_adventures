#pragma once

#include "gfx/color.hpp"
#include "ui/event.hpp"
#include "ui/event_listener.hpp"
#include "ui/label.hpp"
#include "ui/widget.hpp"

namespace ui {

    class Checkbox : public Widget, public EventListener<MouseEvent> {
    private:
        bool m_is_checked{false};

        int m_box_size{32};
        int m_box_spacing{10};
        float m_box_thickness{4};
        gfx::Color m_box_color{gfx::Colors::Black};

        Label m_label;

        [[nodiscard]] RectI box_area() const;

    public:
        Checkbox(std::string&& id, std::string&& label, gfx::Font const& font);
        Checkbox(std::string&& label, gfx::Font const& font);

        Checkbox(Checkbox const&) = delete;
        Checkbox& operator=(Checkbox const&) = delete;
        Checkbox(Checkbox&&) = default;
        Checkbox& operator=(Checkbox&&) = default;
        ~Checkbox() = default;

        void set_area(RectI const area) override;

        void set_margin(Margin const margin) override;

        void render(gfx::Renderer& renderer) const override;

        EventListenerResult handle(MouseEvent const& event) override;
    };
}  // namespace ui
