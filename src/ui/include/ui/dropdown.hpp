#pragma once

#include <any>
#include "ui/event.hpp"
#include "ui/event_dispatcher.hpp"
#include "ui/label.hpp"
#include "ui/panel.hpp"
#include "ui/scene_stack.hpp"
#include "ui/widget.hpp"

namespace ui {

    class WidgetFactory;

    struct DropdownOption final {
        std::string id;
        std::string text;
        std::any value;
    };

    class Dropdown;

    class DropdownScene final : public Scene {
    private:
        SceneStack* m_scene_stack;
        gfx::Font const* m_font;

        std::vector<DropdownOption> m_options;
        bool m_is_dirty{false};
        bool m_is_opened{false};

        Panel m_panel;

        void update(Dropdown const& dropdown);
        void show(Dropdown const& dropdown);
        void hide();

    public:
        DropdownScene(SceneStack& scene_stack, gfx::Font const& font);

        void render(gfx::Renderer& renderer) const override;
        EventListenerResult handle(Event const& event) override;

        void toggle(Dropdown const& dropdown);
        void add_option(std::string_view id, std::string_view text, std::any value);
        void remove_option(std::string_view id);
        void clear_options();
    };

    class Dropdown final : public Widget, public EventListener<MouseEvent> {
    private:
        Label m_label;
        std::unique_ptr<DropdownScene> m_scene;
        gfx::Font const* m_font;
        SceneStack* m_scene_stack;
        EventDispatcher* m_event_dispatcher;

        [[nodiscard]] RectI label_area() const;
        [[nodiscard]] RectI chevron_area() const;

    public:
        Dropdown(
            std::string&& id,
            gfx::Font const& font,
            SceneStack& scene_stack,
            EventDispatcher& event_dispatcher
        );
        Dropdown(gfx::Font const& font, SceneStack& scene_stack, EventDispatcher& event_dispatcher);

        void render(gfx::Renderer& renderer) const override;

        EventListenerResult handle(MouseEvent const& event) override;

        void set_area(RectI const area) override;

        void add_option(std::string_view id, std::string_view text, std::any value);

        void clear_options();

        void remove_option(std::string_view id);
    };
}  // namespace ui
