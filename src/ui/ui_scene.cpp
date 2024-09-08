#include "ui/ui_scene.hpp"

namespace ui {

    void UIScene::render(gfx::Renderer& renderer) const {
        m_panel.render(renderer);
    }

    EventListenerResult UIScene::handle(Event const& event) {
        return m_panel.handle(event);
    }

}  // namespace ui
