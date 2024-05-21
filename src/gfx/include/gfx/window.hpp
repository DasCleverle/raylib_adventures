#pragma once

#include <utils/vec2.hpp>

namespace gfx {
    class Renderer;

    enum class WindowOption { Resizeable = 0 };

    class Window final {
        friend class Renderer;

    private:
        std::size_t m_renderers;

        Window(int width, int height, char const* const title);
        ~Window();

    public:
        Window(Window const&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) = delete;

        static Window& create(int width, int height, char const* const title) {
            static Window s_instance{ width, height, title };
            return s_instance;
        }

        static Window& create(Vec2i size, char const* const title) {
            return create(size.x, size.y, title);
        }

        void set_option(WindowOption const option, bool enabled);

        void set_target_fps(int fps);

        [[nodiscard]] bool should_close() const;

        [[nodiscard]] Vec2i size() const;

        [[nodiscard]] Renderer renderer();
    };
}  // namespace gfx
