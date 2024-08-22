#pragma once

#include "gfx/renderer.hpp"
#include "ui/event_listener.hpp"

namespace ui {
    class Scene : public GenericEventListener {
    public:
        virtual void render(gfx::Renderer& renderer) = 0;
        virtual EventListenerResult handle(Event const& event) override = 0;
    };
}  // namespace ui
