#include "button.hpp"
#include "checkbox.hpp"
#include "event_dispatcher.hpp"
#include "gfx/font_manager.hpp"
#include "label.hpp"

namespace ui {

    template<typename F>
    class WidgetFactory {
    private:
        EventDispatcher* m_dispatcher;
        gfx::FontManager<F>* m_font_manager;

    public:
        WidgetFactory(EventDispatcher& dispatcher, gfx::FontManager<F>& font_manager)
            : m_dispatcher{&dispatcher}, m_font_manager{&font_manager} {}

        WidgetFactory(WidgetFactory const&) = delete;
        WidgetFactory& operator=(WidgetFactory const&) = delete;
        WidgetFactory(WidgetFactory&&) = default;
        WidgetFactory& operator=(WidgetFactory&&) = default;
        ~WidgetFactory() = default;

        Button create_button(std::string&& text) const {
            return Button{std::move(text), m_font_manager->default_font(), *m_dispatcher};
        }

        Button create_button(std::string&& id, std::string&& text) const {
            return Button{
                std::move(id),
                std::move(text),
                m_font_manager->default_font(),
                *m_dispatcher
            };
        }

        Label create_label(std::string&& text) const {
            return Label{std::move(text), m_font_manager->default_font()};
        }

        Checkbox create_checkbox(std::string&& label) const {
            return Checkbox{std::move(label), m_font_manager->default_font(), *m_dispatcher};
        }
    };
}  // namespace ui
