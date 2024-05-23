#pragma once

#include <variant>
#include "gfx/font_manager.hpp"
#include "utils/unique_value.hpp"
#include "utils/vec2.hpp"

namespace gfx {
    class Renderer;

    enum class WindowOption { Resizeable = 0 };

    class Window final {
        friend class Renderer;

    private:
        struct Deleter {
            void operator()(std::monostate) const;
        };

        // This member variable must come first so that its
        // destructor is called last to prevent segfaults
        // when m_font_manager is destructed.
        UniqueValue<std::monostate, Deleter> m_handle;
        std::size_t m_renderers;
        FontManager m_font_manager;

        Window(int width, int height, char const* const title);

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

        [[nodiscard]] FontManager& font_manager();
    };
}  // namespace gfx
