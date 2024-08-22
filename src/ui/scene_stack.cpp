#include "ui/scene_stack.hpp"

namespace ui {

    void SceneStack::pop() {
        m_stack.pop_back();
    }

    void SceneStack::render(gfx::Renderer& renderer) {
        for (auto const& scene : m_stack) {
            scene->render(renderer);
        }
    }

    EventListenerResult SceneStack::handle(Event const& event) {
        for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it) {
            auto result = (*it)->handle(event);

            if (result == EventListenerResult::Handled) {
                return EventListenerResult::Handled;
            }
        }

        return EventListenerResult::Continue;
    }

}  // namespace ui
