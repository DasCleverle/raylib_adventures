#pragma once

#include <deque>
#include <memory>

#include "gfx/renderer.hpp"
#include "scene.hpp"
#include "ui/event_listener.hpp"

namespace ui {

    class SceneStack final : public GenericEventListener {
    private:
        std::deque<std::pair<Scene*, std::optional<std::size_t>>> m_stack;
        std::vector<std::unique_ptr<Scene>> m_managed_scenes;

    public:
        SceneStack(SceneStack const&) = delete;
        SceneStack& operator=(SceneStack const&) = delete;
        SceneStack(SceneStack&&) = delete;
        SceneStack& operator=(SceneStack&&) = delete;

        SceneStack() = default;
        ~SceneStack() = default;

        template<std::derived_from<Scene> T, typename... Args>
        void emplace_back(Args... args) {
            m_managed_scenes.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            m_stack.emplace_back(m_managed_scenes.back().get(), m_stack.size());
        }

        template<std::derived_from<Scene> T>
        void push_back(T& scene) {
            m_stack.emplace_back(&scene, std::nullopt);
        }

        void pop();

        void render(gfx::Renderer& renderer);

        EventListenerResult handle(Event const& event) override;
    };

}  // namespace ui
