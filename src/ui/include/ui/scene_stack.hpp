#pragma once

#include <deque>
#include <memory>

#include "gfx/renderer.hpp"
#include "scene.hpp"
#include "ui/event_listener.hpp"

namespace ui {

    class SceneStack final : public GenericEventListener {
    private:
        std::deque<std::unique_ptr<Scene>> m_stack;

    public:
        SceneStack(SceneStack const&) = delete;
        SceneStack& operator=(SceneStack const&) = delete;
        SceneStack(SceneStack&&) = delete;
        SceneStack& operator=(SceneStack&&) = delete;

        SceneStack() = default;
        ~SceneStack() = default;

        template<typename T, typename... Args>
        void emplace_back(Args... args) {
            m_stack.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

        void pop();

        void render(gfx::Renderer& renderer);

        EventListenerResult handle(Event const& event) override;
    };

}  // namespace ui
