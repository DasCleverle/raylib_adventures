#include "ui/scene_stack.hpp"

#include <iterator>

namespace ui {

    void SceneStack::pop() {
        auto [_, index] = m_stack.back();

        m_stack.pop_back();

        if (index.has_value()) {
            m_managed_scenes.erase(std::next(m_managed_scenes.begin(), index.value()));
        }
    }

    void SceneStack::render(gfx::Renderer& renderer) {
        for (auto const& [scene, _] : m_stack) {
            scene->render(renderer);
        }
    }

    EventListenerResult SceneStack::handle(Event const& event) {
        for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it) {
            auto [scene, _] = *it;
            auto result = scene->handle(event);

            if (result == EventListenerResult::Handled) {
                return EventListenerResult::Handled;
            }
        }

        return EventListenerResult::Continue;
    }

}  // namespace ui
