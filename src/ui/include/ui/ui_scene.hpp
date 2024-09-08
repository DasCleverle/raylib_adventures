#pragma once

#include "scene.hpp"
#include "ui/panel.hpp"

namespace ui {

    class UIScene final : public Scene {
    private:
        Panel m_panel;

    public:
        UIScene(Panel&& panel)
            : m_panel{std::move(panel)} {}

        void render(gfx::Renderer& renderer) const override;
        EventListenerResult handle(Event const& event) override;
    };

}  // namespace ui
