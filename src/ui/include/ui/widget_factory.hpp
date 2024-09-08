#include "button.hpp"
#include "checkbox.hpp"
#include "event_dispatcher.hpp"
#include "label.hpp"
#include "ui/dropdown.hpp"
#include "ui/scene_stack.hpp"
#include "ui/textbox.hpp"

namespace ui {

    class WidgetFactory {
    private:
        EventDispatcher* m_dispatcher;
        gfx::Font const* m_default_font;
        SceneStack* m_scene_stack;

    public:
        WidgetFactory(EventDispatcher& dispatcher, gfx::Font const& default_font, SceneStack& scene_stack)
            : m_dispatcher{&dispatcher},
              m_default_font{&default_font},
              m_scene_stack{&scene_stack} {}

        WidgetFactory(WidgetFactory const&) = default;
        WidgetFactory& operator=(WidgetFactory const&) = default;
        WidgetFactory(WidgetFactory&&) = default;
        WidgetFactory& operator=(WidgetFactory&&) = default;
        ~WidgetFactory() = default;

        Button create_button(std::string&& text) const {
            return Button{std::move(text), *m_default_font, *m_dispatcher};
        }

        Button create_button(std::string&& id, std::string&& text) const {
            return Button{std::move(id), std::move(text), *m_default_font, *m_dispatcher};
        }

        Label create_label(std::string&& text) const {
            return Label{std::move(text), *m_default_font};
        }

        Checkbox create_checkbox(std::string&& label) const {
            return Checkbox{std::move(label), *m_default_font, *m_dispatcher};
        }

        Textbox create_textbox() const {
            return Textbox{*m_default_font};
        }

        Dropdown create_dropdown() const {
            return Dropdown{*m_default_font, *m_scene_stack, *m_dispatcher};
        }
    };
}  // namespace ui
